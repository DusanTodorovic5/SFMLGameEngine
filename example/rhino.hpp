#ifndef RHINO_CLASS
#define RHINO_CLASS

#include "frog.hpp"
#include "EngineDirectory/sceneManager.hpp"
#include <cmath>
class Rhino : public Node{
    public:
        Rhino() : Node("rhino"){
            AnimatedSprite* spr = new AnimatedSprite(this);
            spr->addSpriteSheet("idle", new SpriteSheet("enemy/rhinoIdle.png", 100, true, spr, 52, 34));
            spr->addSpriteSheet("hit", new SpriteSheet("enemy/rhinoHit.png", 100, false, spr, 52, 34));
            spr->addSpriteSheet("run", new SpriteSheet("enemy/rhinoRun.png", 100, true, spr, 52, 34));
            spr->setAnimation("idle");
            spr->setSize(64,64);
            Collision* col = new Collision(this,true,false);
            col->setRectangle(sf::FloatRect(0,0,64,64));
            setComponent(spr);
            setComponent(col);
            frog = nullptr;
            accelerationX = 0;
            accelerationY = 0;
            stoppedRunning = true;
        }
        virtual void start(){
            frog = (Frog*)SceneManager::manager()->getCurrentScene()->getNodeByName("character");
        }
        virtual void update(){
            if (((AnimatedSprite*)getComponent("AnimatedSprite"))->getCurrentAnimation() != "hit" && stoppedRunning)
            if (frog && ((frog->getPosition().y < getPosition().y && frog->getPosition().y > getPosition().y - 64) || 
                    (getPosition().y < frog->getPosition().y && getPosition().y > frog->getPosition().y - 72))){
                if (std::abs(frog->getPosition().x - getPosition().x) < 200){
                    ((AnimatedSprite*)getComponent("AnimatedSprite"))->setAnimation("run");
                    if (frog->getPosition().x < getPosition().x){
                        //s leva
                        ((AnimatedSprite*)getComponent("AnimatedSprite"))->setOrientation(false);
                        velocity.x = -20;
                        accelerationX = 1;
                    }
                    else{
                        ((AnimatedSprite*)getComponent("AnimatedSprite"))->setOrientation(true);
                        velocity.x = 20;
                        accelerationX = -1;
                    }
                    stoppedRunning = false;
                } else{
                    ((AnimatedSprite*)getComponent("AnimatedSprite"))->setAnimation("idle");
                }
            }
            velocity.x += accelerationX;
            if (velocity.x == 0){
                accelerationX = 0;
                stoppedRunning = true;
            }
        }
        virtual void processInput(sf::Event::EventType, sf::Event::KeyEvent){

        }
        void animationFinished(std::string s){
            SceneManager::manager()->getCurrentScene()->destroy(this);
        }
        void killed(){
            removeComponent("Collision");
            ((AnimatedSprite*)getComponent("AnimatedSprite"))->setAnimation("hit");
        }
    private:
        Frog* frog;
        int accelerationX;
        int accelerationY;
        bool stoppedRunning;
};

#endif