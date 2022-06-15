#ifndef FRUIT_CLASS
#define FRUIT_CLASS

#include "EngineDirectory/node.hpp"

class Fruit : public Node{
    public:
        Fruit() : Node("fruit"){

        }
        void start(){

        }
        void update(){

        }
        void _draw(sf::RenderTarget& target, sf::RenderStates states) const{

        }
        void processInput(sf::Event::EventType, sf::Event::KeyEvent){
            
        }
        virtual int getPoints() = 0;
};


#endif