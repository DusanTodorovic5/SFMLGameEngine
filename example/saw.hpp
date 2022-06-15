#ifndef SAW_CLASS
#define SAW_CLASS

#include "EngineDirectory/node.hpp"
#include "EngineDirectory/animatedSprite.hpp"
#include "EngineDirectory/collision.hpp"
class Saw : public Node{
    public:
        Saw() : Node("saw"){
            AnimatedSprite* spr = new AnimatedSprite(this);
            spr->addSpriteSheet("idle", new SpriteSheet("enemy/saw.png", 100, true, spr, 38, 38));
            spr->setAnimation("idle");
            spr->setSize(64,64);
            Collision* col = new Collision(this,true,false);
            col->setRectangle(sf::FloatRect(0,0,64,64));
            setComponent(spr);
            setComponent(col);
        }
        void start(){
            
        }
        virtual void update(){
            
        }
        void processInput(sf::Event::EventType, sf::Event::KeyEvent){

        }
};

#endif