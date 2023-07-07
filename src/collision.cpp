#include "collision.hpp"
#include "component.hpp"
#include <iostream>

Collision::Collision(Node *owner, bool movable, bool rigid) : Component("Collision")
{
    this->owner = owner;
    offset = sf::Vector2f(0, 0);
    lastPos.x = owner->getPosition().x;
    lastPos.y = owner->getPosition().y;
    this->movable = movable;
    this->rigid = rigid;
    this->hadCol = sf::IntRect(0, 0, 0, 0);
}
void Collision::setRectangle(sf::FloatRect rect)
{
    this->rect = rect;
}
sf::Vector2f Collision::getSize()
{
    return sf::Vector2f(rect.width, rect.height);
}
sf::Vector2f Collision::getPosition()
{
    return sf::Vector2f(rect.left, rect.top);
}
void Collision::setPosition(sf::Vector2f position)
{
    lastPos = sf::Vector2f(rect.left, rect.top);
    rect.top = position.y + offset.y;
    rect.left = position.x + offset.x;
}
void Collision::checkCollision(Collision &collision)
{
    if (collision.rigid && movable)
    {
        sf::FloatRect myRect = rect;
        sf::FloatRect colRect = collision.rect;
        myRect.top += owner->velocity.y;
        myRect.left += owner->velocity.x;
        lastRect = myRect;
        if (myRect.intersects(colRect))
        {
            int yDir = 0;
            int xDir = 0;
            sf::Vector2f newVelocity(owner->velocity.x, owner->velocity.y);

            myRect.left -= owner->velocity.x;
            if (owner->velocity.y)
            {
                if (owner->velocity.y > 0 &&
                    myRect.top < colRect.top && myRect.top + myRect.height < colRect.top + colRect.height &&
                    myRect.left < colRect.left + colRect.width && myRect.left + myRect.width > colRect.left)
                {

                    newVelocity.y = 0;
                    yDir = 1;
                    this->hadCol.top = 1;
                }
                else if (owner->velocity.y < 0 &&
                         myRect.top > colRect.top && myRect.top + myRect.height > colRect.top + colRect.height &&
                         myRect.left < colRect.left + colRect.width && myRect.left + myRect.width > colRect.left)
                {

                    newVelocity.y = 0;
                    yDir = -1;
                    this->hadCol.height = 1;
                }
            }
            myRect.left += owner->velocity.x;
            myRect.top -= owner->velocity.y;
            if (owner->velocity.x)
            {
                if (owner->velocity.x > 0 &&
                    myRect.left < colRect.left && myRect.left + myRect.width < colRect.left + colRect.width &&
                    myRect.top < colRect.top + colRect.height && myRect.top + myRect.height > colRect.top)
                {

                    newVelocity.x = 0;
                    xDir = 1;
                    this->hadCol.left = 1;
                }
                else if (owner->velocity.x < 0 &&
                         myRect.left > colRect.left && myRect.left + myRect.width > colRect.left + colRect.width &&
                         myRect.top < colRect.top + colRect.height && myRect.top + myRect.height > colRect.top)
                {

                    newVelocity.x = 0;
                    xDir = -1;
                    this->hadCol.width = 1;
                }
            }

            owner->onCollision(sf::Vector2f(xDir, yDir), collision.owner);
            owner->setVelocity(newVelocity);
        }
    }
    else if (!collision.rigid && rigid)
    {
        sf::FloatRect myRect = rect;
        sf::FloatRect colRect = collision.rect;
        myRect.top += owner->velocity.y;
        myRect.left += owner->velocity.x;
        lastRect = myRect;
        if (myRect.intersects(colRect))
        {
            owner->onCollide(sf::Vector2f(0, 0), collision.owner);
            collision.owner->onCollide(sf::Vector2f(0, 0), owner);
            inside.insert(std::pair<Node *, Node *>(collision.owner, collision.owner));
        }
    }
}
void Collision::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape sp;
    sp.setFillColor(sf::Color::Transparent);
    sp.setOutlineColor(sf::Color::Green);
    sp.setOutlineThickness(3);
    sp.setPosition(rect.left, rect.top);
    sp.setSize(sf::Vector2f(rect.width, rect.height));
    target.draw(sp, states);
}
void Collision::setOffset(sf::Vector2f offset)
{
    this->offset = offset;
}
bool Collision::getRigid()
{
    return rigid;
}
void Collision::hadCollision()
{
    static int i = 0;
    owner->noCollision(hadCol);
    this->hadCol = sf::IntRect(0, 0, 0, 0);
    int t = 0;
    for (std::pair<Node *, Node *> node : lastInside)
    {
        try
        {

            Node *l = inside.at(node.first);
        }
        catch (std::out_of_range oof)
        {
            owner->exitCollide(node.first);
        }
    }

    lastInside = inside;
    inside.clear();
}
void Collision::destroyed(Node *n)
{
    try
    {
        Node *n = lastInside.at(n);
        lastInside.erase(n);
    }
    catch (std::out_of_range oof)
    {
    }
}