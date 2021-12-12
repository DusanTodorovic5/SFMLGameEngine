#ifndef NODE_CLASS
#define NODE_CLASS

#include <SFML/Graphics.hpp>
#include <map>
#include "component.hpp"
class Node:public sf::Drawable{
    public:
        Node(std::string tag="");
        virtual void start()=0;
        virtual void update()=0;
        virtual void _draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void onCollision(sf::Vector2f, Node*);
        virtual void noCollision(sf::IntRect);
        virtual void onCollide(sf::Vector2f, Node*);
        virtual void exitCollide(Node*);
        virtual void processInput(sf::Event::EventType, sf::Event::KeyEvent) = 0;
        Component* getComponent(std::string);
        void setComponent(Component*);
        void removeComponent(std::string);
        virtual void animationFinished(std::string);
        void focusChange(bool);
        void move(double,double);
        sf::Vector2f getPosition() const;
        virtual void setPosition(sf::Vector2f position);
        virtual void setPosition(double,double);
        void incVelocity(sf::Vector2f);
        void incVelocity(double,double);
        void setVelocity(sf::Vector2f);
        sf::Vector2f getVelocity();
        void applyVelocity();
        std::string getTag();
        void setName(std::string);
        std::string getName();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        ~Node();
    protected:
        sf::Vector2f getLastPosition();
        sf::Vector2f position;
        sf::Vector2f velocity;
        std::string tag;
        std::map<std::string, Component*> components;
    private:
        friend class Collision;
        friend class EmptyNode; 
        std::string name;
        
};

#endif