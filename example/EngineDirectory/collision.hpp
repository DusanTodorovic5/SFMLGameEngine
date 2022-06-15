#ifndef COLLISION_CLASS
#define COLLISION_CLASS

#include "component.hpp"
#include "node.hpp"

class Collision : public Component{
    public:
        Collision(Node* owner, bool movable = false, bool rigid = true);
        void setRectangle(sf::FloatRect rect);
        sf::Vector2f getSize();
        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f position);
        void checkCollision(Collision&);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void setOffset(sf::Vector2f);
        bool getRigid();
        void hadCollision();
        void destroyed(Node*);
    private:
        sf::Vector2f lastPos;
        sf::Vector2f offset;
        Node* owner;
        sf::FloatRect rect;
        sf::FloatRect lastRect;
        bool movable;
        bool rigid;
        sf::IntRect hadCol;
        std::map<Node*,Node*> inside;
        std::map<Node*,Node*> lastInside;
};

#endif