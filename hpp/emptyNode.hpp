#ifndef EMPTY_NODE
#define EMPTY_NODE
#include "node.hpp"
class EmptyNode : public Node{
    public:
        EmptyNode(std::string tag="");
        void start();
        void update();
        virtual void _draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void processInput(sf::Event::EventType, sf::Event::KeyEvent);
};

#endif