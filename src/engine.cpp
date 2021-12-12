#include "engine.hpp"
#include <iostream>

Engine* Engine::instance = nullptr;

Engine::Engine():window(sf::VideoMode(1500, 900), ""){
    started = false;
    debug = false;
    view = new sf::View(sf::FloatRect(0,0,1000,600));
}
Engine* Engine::engine(){
    if (instance == nullptr){
        instance = new Engine();
    }
    return instance;
}
bool Engine::debugMode(){
    return this->debug;
}
void Engine::setDebugMode(bool debug){
    this->debug = debug;
}
void Engine::start(){
    if (started) return;
    started = true;
        
    window.setFramerateLimit(60);
    window.setView(*view);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                SceneManager::manager()->switchScene("sc1");
            }
            SceneManager::manager()->getCurrentScene()->processInput(event.type,event.key);


        }
        
        SceneManager::manager()->getCurrentScene()->update();
        SceneManager::manager()->getCurrentScene()->checkCollision();
        SceneManager::manager()->getCurrentScene()->applyMovement();
        SceneManager::manager()->getCurrentScene()->lateDestroy();
        window.clear();
        window.setView(*this->view);
        window.draw(*(SceneManager::manager()->getCurrentScene()));
        window.display();
    }
}
sf::View* Engine::getView(){
    return this->view;
}
sf::Vector2u Engine::getWindowSize() const{
    return this->window.getSize();
}
void Engine::setWindowSize(sf::Vector2u size){
    window.setSize(size);
}