#ifndef TEXT_CLASS
#define TEXT_CLASS
#include "uiNode.hpp"
class Text : public UINode{
    public:
        Text(std::string font = "font.ttf");
        void start();
        void update();
        void _draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void processInput(sf::Event::EventType, sf::Event::KeyEvent);
        void setColor(sf::Color);
        std::string getText() const;
        void setText(std::string text);
    private:
        std::string text;
        sf::Font font;
        sf::Color color;
};

#endif