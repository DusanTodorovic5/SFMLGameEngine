#ifndef ANIMATED_SPRITE_CLASS
#define ANIMATED_SPRITE_CLASS

#include <SFML/Graphics.hpp>
#include <thread>
#include "semaphore.hpp"
#include <map>
#include "spriteSheet.hpp"
#include <chrono>
#include "component.hpp"
class Node;
class AnimatedSprite : public Component
{
public:
    AnimatedSprite(Node *owner = nullptr);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void addSpriteSheet(std::string, SpriteSheet *);
    void setAnimation(std::string);
    void animationFinished();
    ~AnimatedSprite();
    void update();
    void move(double, double);
    void setOrientation(bool);
    void setSize(double, double);
    void setPosition(double, double);
    void pause();
    void resume();
    sf::Vector2f getPosition();
    std::string getCurrentAnimation();

private:
    std::map<std::string, SpriteSheet *> mapa;
    double width;
    double height;
    std::thread *thread;
    Semaphore *sem;
    Semaphore *pauseSem;
    std::condition_variable cv;
    std::mutex waitUntilMutex;
    bool isPaused = false;
    SpriteSheet *currSpriteSheet;
    std::string currName;
    bool running;
    bool orientation; // left true
    Node *owner;
};

#endif