#ifndef BEE_CLASS
#define BEE_CLASS
#include "EngineDirectory/node.hpp"
#include "EngineDirectory/animatedSprite.hpp"
#include "EngineDirectory/collision.hpp"
#include <iostream>
class Bee : public Node{
    public:
        Bee() : Node("bee"){
            AnimatedSprite* spr = new AnimatedSprite(this);
            spr->addSpriteSheet("idle", new SpriteSheet("enemy/bee.png", 100, true, spr, 36, 34));
            spr->addSpriteSheet("hit", new SpriteSheet("enemy/beeHit.png", 100, false, spr, 36, 34));
            spr->setAnimation("idle");
            spr->setSize(64,64);
            Collision* col = new Collision(this,true,false);
            col->setRectangle(sf::FloatRect(0,0,64,64));
            setComponent(spr);
            setComponent(col);

            gravity = 3;
            accelerationX = accelerationY = 0;
            gravityTime = false;
        }
        virtual void start(){

        }
        virtual void update(){
            if (gravityTime){
                velocity.y += gravity;
            }
            if (accelerationX != 0){
                velocity.x = accelerationX;
                accelerationX++;
                //if (accelerationX == 0)
                    //velocity.x = 0;
            }
            
            if (accelerationY != 0){
                velocity.y = accelerationY;
                
                if (accelerationY != 0){
                    gravityTime = true;
                    accelerationY++;
                }
                    
                
            }
            
        }
        virtual void onCollision(sf::Vector2f, Node*){

        }
        virtual void noCollision(sf::IntRect){

        }
        virtual void onCollide(sf::Vector2f, Node*){

        }
        virtual void exitCollide(Node*){

        }
        virtual void processInput(sf::Event::EventType, sf::Event::KeyEvent){
            
        }
        void animationFinished(std::string s){
            SceneManager::manager()->getCurrentScene()->destroy(this);
        }
        void killed(){
            removeComponent("Collision");
            accelerationX = -4;
            accelerationY = -5;
            ((AnimatedSprite*)getComponent("AnimatedSprite"))->setAnimation("hit");
        }
        private:
            int gravity;
            int accelerationX;
            int accelerationY;
            bool gravityTime;
};

#endif