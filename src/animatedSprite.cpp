#include "animatedSprite.hpp"
#include <iostream>
#include "node.hpp"
AnimatedSprite::AnimatedSprite(Node* owner):Component("AnimatedSprite"){
    sem = new Semaphore(1);
    pauseSem = new Semaphore(0);
    thread = nullptr;
    currSpriteSheet = nullptr;
    running = false;
    orientation = true;
    currName = "";
    isPaused = false;
    this->owner = owner;
}
void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sem->wait();
    target.draw(currSpriteSheet->getSprite());
    sem->notify();
}
void AnimatedSprite::setAnimation(std::string name){
    if (currName == name){
        return;
    }
    sem->wait();
    sf::Vector2f lastPosition(0,0);
    if (currSpriteSheet){
        currSpriteSheet->reset();
        lastPosition = currSpriteSheet->getSprite().getPosition();
    }
    currSpriteSheet = mapa[name];
    currName = name;
    currSpriteSheet->getSprite().setPosition(lastPosition);
    sem->notify();
    if (thread == nullptr){
        running = true;
        thread = new std::thread(&AnimatedSprite::update, this);
    }
    if (thread && !running){
        cv.notify_all();
        thread->join();
        delete thread;
        running = true;
        thread = new std::thread(&AnimatedSprite::update, this);
    }
    
}
void AnimatedSprite::addSpriteSheet(std::string name, SpriteSheet* spriteSheet){
    mapa.insert(std::pair<std::string, SpriteSheet*>(name, spriteSheet));
}
void AnimatedSprite::animationFinished(){
    std::string currAnim = currName;
    running = false;
    currName = "";
    currSpriteSheet->reset();
    //std::cout << "Zavrseno" << std::endl;
    if (owner){
        owner->animationFinished(currAnim);
    }
}
AnimatedSprite::~AnimatedSprite(){
    cv.notify_all();
    if (thread){
        running = false;
        pauseSem->notify();
        thread->join();
    }
    delete thread;
    delete sem;
    delete pauseSem;
}
void AnimatedSprite::update(){
    std::unique_lock<std::mutex> lk(waitUntilMutex);
    while (running){
        auto now = std::chrono::system_clock::now();
        if (cv.wait_until(lk,now + std::chrono::milliseconds(currSpriteSheet->getWaitTime()))  == std::cv_status::timeout){
            sem->wait();
            currSpriteSheet->update(orientation);
            sem->notify();
            if (isPaused){
                pauseSem->wait();
            }
        }
        else{
            break;
        }
    }
}
void AnimatedSprite::move(double x,double y){
    sem->wait();
    if (currSpriteSheet){
        currSpriteSheet->getSprite().move(x,y);
    }
    sem->notify();
}
void AnimatedSprite::setOrientation(bool orientation){
    sem->wait();
    this->orientation = orientation;
    currSpriteSheet->update(orientation,0);
    sem->notify();
}
void AnimatedSprite::setSize(double x, double y){
    sem->wait();
    std::map<std::string, SpriteSheet*>::iterator it;
    for (it = mapa.begin(); it != mapa.end(); it++)
    {
        mapa[it->first]->getSprite().setScale(x/mapa[it->first]->getSprite().getGlobalBounds().width,
                        y/mapa[it->first]->getSprite().getGlobalBounds().height);
    }
    sem->notify();
}
void AnimatedSprite::setPosition(double x,double y){
    sem->wait();

    currSpriteSheet->getSprite().setPosition(x,y);

    sem->notify();
}
sf::Vector2f AnimatedSprite::getPosition(){
    return currSpriteSheet->getSprite().getPosition();
}
std::string AnimatedSprite::getCurrentAnimation(){
    return currName;
}
void AnimatedSprite::pause(){
    sem->wait();
    if (!isPaused){
        isPaused = true;
    }
    sem->notify();
}
void AnimatedSprite::resume(){
    sem->wait();
    if (isPaused){
        isPaused = false;
        pauseSem->notify();
    }
    sem->notify();
}