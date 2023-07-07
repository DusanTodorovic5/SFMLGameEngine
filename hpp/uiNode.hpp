#ifndef UI_NODE
#define UI_NODE

#include "node.hpp"

class UINode : public Node
{
public:
    UINode();
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void _draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    virtual void processInput(sf::Event::EventType, sf::Event::KeyEvent) = 0;
    virtual void setPosition(sf::Vector2f position);
    virtual void setPosition(double, double);
    void refresh();

private:
    sf::Vector2f offset;
};

#endif