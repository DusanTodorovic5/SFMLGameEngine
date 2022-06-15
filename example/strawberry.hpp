#ifndef STRAWBERRY_FRUIT_CLASS
#define STRAWBERRY_FRUIT_CLASS

#include "fruit.hpp"
#include "EngineDirectory/animatedSprite.hpp"
#include "EngineDirectory/collision.hpp"
class Strawberry : public Fruit{
    public:
        Strawberry(){
            AnimatedSprite* spr = new AnimatedSprite(this);
            SpriteSheet* sprSheet = new SpriteSheet("items/strawberry.png",100,true,spr);
            spr->addSpriteSheet("anim",sprSheet);
            spr->setAnimation("anim");
            setComponent(spr);
           // spr->setSize(256,256);
            Collision* col = new Collision(this,false,false);
            col->setRectangle(sf::FloatRect(0,0,32,32));
            col->setOffset(sf::Vector2f(16,16));
            setComponent(col);
        }
        int getPoints(){
            return 3;
        }
};


#endif