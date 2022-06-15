#ifndef FROG_CLASS
#define FROG_CLASS
#include "EngineDirectory/node.hpp"
#include "EngineDirectory/animatedSprite.hpp"
#include "EngineDirectory/collision.hpp"
#include "EngineDirectory/emptyNode.hpp"
#include "EngineDirectory/text.hpp"
class Frog : public Node{
    public:
        Frog();
        void start();
        void update();
        virtual void _draw(sf::RenderTarget &target, sf::RenderStates states) const;
        
        void processInput(sf::Event::EventType, sf::Event::KeyEvent);
        void updateMovement();
        void jump();
        void onCollision(sf::Vector2f,Node*);
        
        void noCollision(sf::IntRect);
        void onCollide(sf::Vector2f, Node*);
        void exitCollide(Node*);
        void animationFinished(std::string);
    private:
        AnimatedSprite *sprite;
        Collision* collision;
        float x = 0;
        float y = 0;
        float accelerationX = 0;
        float accelerationY = 0;
        int speed = 5;
        float gravity = 2;
        int jumped = 0;
        bool grounded = false;
        float ground = 720;
        int score;
        Text* text;
        EmptyNode* container;
        bool hitFinished = false;
};

#endif