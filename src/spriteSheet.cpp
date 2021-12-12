#include "spriteSheet.hpp"
#include "animatedSprite.hpp"
SpriteSheet::SpriteSheet(std::string textureName, int duration, bool loop, AnimatedSprite* owner, double width, double height){
    texture.loadFromFile(textureName);
    sprite.setTexture(texture);
    this->duration = duration;
    this->isLoop = loop;
    this->owner = owner;
    currFrame = 0;
    if (width != 0){
        int x = texture.getSize().x;
        maxFrame = x/width;
        this->width = width;
        this->height = height;
    }
    else{
        int x = texture.getSize().x;
        int y = texture.getSize().y;
        maxFrame = x/y;
        this->width = this->height = y;
    }
    sprite.setTextureRect(sf::IntRect(0,0,width,height));
    sprite.setPosition(0,0);
}
sf::Sprite& SpriteSheet::getSprite(){
    return sprite;
}
void SpriteSheet::reset(){
    currFrame = 0;
}
void SpriteSheet::update(bool orientation, int increment){
    if (!isLoop && currFrame + increment == maxFrame){
        if (owner != nullptr){
            owner->animationFinished();
        }
        return;
    }
    currFrame = (currFrame + increment)%maxFrame;
    if (orientation)
        sprite.setTextureRect(sf::IntRect(currFrame*width + width, 0, -width, height));
    else
        sprite.setTextureRect(sf::IntRect(currFrame*width, 0, width, height));
}
int SpriteSheet::getWaitTime(){
    return duration;
}