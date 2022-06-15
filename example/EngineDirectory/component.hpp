#ifndef COMPONENT_CLASS
#define COMPONENT_CLASS
#include <string>
#include <SFML/Graphics.hpp>
class Component : public sf::Drawable{
    public:
        std::string getType();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    protected:
        Component(std::string type);
        void setType(std::string type);
    private:
        std::string type;
};

#endif