#include "node.hpp"
#include <iostream>
#include "animatedSprite.hpp"
#include "sprite.hpp"
#include "collision.hpp"
#include "engine.hpp"
Node::Node(std::string tag)
{
    velocity = sf::Vector2f(0, 0);
    this->tag = tag;
    name = "";
}

Node::~Node()
{
    for (std::pair<std::string, Component *> component : this->components)
    {
        delete component.second;
    }
}

Component *Node::getComponent(std::string type)
{
    return components.at(type);
}
void Node::setComponent(Component *component)
{
    components.insert(std::pair<std::string, Component *>(component->getType(), component));
}
void Node::removeComponent(std::string name)
{
    Component *t = getComponent(name);
    components.erase(name);
    SceneManager::manager()->getCurrentScene()->destroyComponent(t);
}
void Node::animationFinished(std::string anim)
{
}
void Node::focusChange(bool focus)
{
    if (!focus)
    {
        try
        {
            ((AnimatedSprite *)(components.at("AnimatedSprite")))->pause();
        }
        catch (std::out_of_range oof)
        {
        }
    }
    else
    {
        try
        {
            ((AnimatedSprite *)(components.at("AnimatedSprite")))->resume();
        }
        catch (std::out_of_range oof)
        {
        }
    }
}
void Node::move(double x, double y)
{
    this->position = sf::Vector2f(this->position.x + x, this->position.y + y);
    try
    {
        ((AnimatedSprite *)getComponent("AnimatedSprite"))->setPosition(this->position.x, this->position.y);
    }
    catch (std::out_of_range)
    {
    }
    try
    {
        ((Sprite *)getComponent("Sprite"))->getSprite().setPosition(this->position);
    }
    catch (std::out_of_range)
    {
    }
    try
    {
        ((Collision *)getComponent("Collision"))->setPosition(sf::Vector2f(this->position.x, this->position.y));
    }
    catch (std::out_of_range)
    {
    }
}
sf::Vector2f Node::getPosition() const
{
    return this->position;
}
void Node::setPosition(sf::Vector2f position)
{
    this->position = position;
    try
    {
        ((AnimatedSprite *)getComponent("AnimatedSprite"))->setPosition(this->position.x, this->position.y);
    }
    catch (std::out_of_range)
    {
    }
    try
    {
        ((Sprite *)getComponent("Sprite"))->getSprite().setPosition(this->position);
    }
    catch (std::out_of_range)
    {
    }
    try
    {
        ((Collision *)getComponent("Collision"))->setPosition(sf::Vector2f(this->position.x, this->position.y));
    }
    catch (std::out_of_range)
    {
    }
}
void Node::setPosition(double x, double y)
{
    setPosition(sf::Vector2f(x, y));
}
void Node::incVelocity(sf::Vector2f relativeVelocity)
{
    velocity += relativeVelocity;
}
void Node::incVelocity(double x, double y)
{
    incVelocity(sf::Vector2f(x, y));
}
void Node::setVelocity(sf::Vector2f newVelocity)
{
    velocity = newVelocity;
}
void Node::applyVelocity()
{
    move(velocity.x, velocity.y);
}
std::string Node::getTag()
{
    return tag;
}
void Node::onCollision(sf::Vector2f, Node *node)
{
}
void Node::noCollision(sf::IntRect)
{
}
sf::Vector2f Node::getVelocity()
{
    return velocity;
}
void Node::onCollide(sf::Vector2f, Node *)
{
}
void Node::exitCollide(Node *)
{
}
void Node::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Collision *col = nullptr;
    for (std::pair<std::string, Component *> component : this->components)
    {
        if (component.first == "Collision")
        {
            col = (Collision *)component.second;
        }
        else
        {
            target.draw(*(component.second), states);
        }
    }
    if (col && Engine::engine()->debugMode())
    {
        target.draw(*col, states);
    }
    _draw(target, states);
}
void Node::_draw(sf::RenderTarget &target, sf::RenderStates states) const
{
}
void Node::setName(std::string name)
{
    this->name = name;
}
std::string Node::getName()
{
    return name;
}