#ifndef SPRITE_CLASS
#define SPRITE_CLASS

#include <SFML/Graphics.hpp>
#include "component.hpp"

class Sprite : public Component{
    public:
        Sprite(std::string texture);
        sf::Sprite& getSprite();
        virtual void start();
        virtual void update();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void setSize(double x,double y);
        void setPosition(sf::Vector2f position);
        void setPosition(double x, double y);
    private:
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif