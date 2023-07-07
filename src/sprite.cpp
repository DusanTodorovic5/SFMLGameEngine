#include "sprite.hpp"

Sprite::Sprite(std::string texture) : Component("Sprite")
{
    this->texture.loadFromFile(texture);
    sprite.setTexture(this->texture);
}
sf::Sprite &Sprite::getSprite()
{
    return this->sprite;
}
void Sprite::start()
{
}
void Sprite::update()
{
}
void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
void Sprite::setSize(double x, double y)
{
    sprite.setScale(x / sprite.getLocalBounds().width, y / sprite.getLocalBounds().height);
}
void Sprite::setPosition(sf::Vector2f position)
{
    sprite.setPosition(position);
}
void Sprite::setPosition(double x, double y)
{
    sprite.setPosition(x, y);
}