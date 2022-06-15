#ifndef PLATFORM_CLASS
#define PLATFORM_CLASS

#include "EngineDirectory/node.hpp"
#include "EngineDirectory/collision.hpp"
#include "EngineDirectory/sprite.hpp"
#include "EngineDirectory/sceneManager.hpp"
#include <vector>
class Platform : public Node{
    public:
        Platform(int count = 0, int orientation = 0){ //orientation 0 left to right, 1 up-down
            this->count = count;
            this->orientation = orientation;
        }
        void start(){
            for (int i=0;i<count;i++){
                Tile* t = new Tile();
                t->setPosition(getPosition().x + 64*i*(1-orientation),getPosition().y + 64*i*orientation);
                SceneManager::manager()->getCurrentScene()->instantiate(t,this);
            }
        }
        void update(){

        }
        void processInput(sf::Event::EventType, sf::Event::KeyEvent){

        }
    private:
        class Tile : public Node{
            public:
                Tile() : Node("ground"){
                    Collision* col = new Collision(this);
                    col->setRectangle(sf::FloatRect(0,0,64,64));
                    Sprite* spr = new Sprite("platforms/platform1.png");
                    spr->setSize(64,64);
                    setComponent(col);
                    setComponent(spr);
                }
                void start(){

                }
                void update(){

                }
                void processInput(sf::Event::EventType, sf::Event::KeyEvent){

                }
        };
        int count;
        int orientation;
       // std::vector<Tile*> tiles;
};

#endif