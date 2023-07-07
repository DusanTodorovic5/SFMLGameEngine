#include "text.hpp"

Text::Text(std::string font) : color(sf::Color::White)
{
    this->font.loadFromFile(font);
}
void Text::start()
{
}
void Text::update()
{
}
void Text::_draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Text text(this->text, font);
    text.setPosition(getPosition());
    text.setFillColor(color);
    text.setCharacterSize(30);
    target.draw(text, states);
}
void Text::processInput(sf::Event::EventType, sf::Event::KeyEvent)
{
}
void Text::setColor(sf::Color color)
{
    this->color = color;
}

std::string Text::getText() const
{
    return text;
}
void Text::setText(std::string text)
{
    this->text = text;
}