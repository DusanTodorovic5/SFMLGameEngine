#ifndef SPRITE_SHEET_CLASS
#define SPRITE_SHEET_CLASS
#include <SFML/Graphics.hpp>
class AnimatedSprite;
class SpriteSheet{
    public:
        SpriteSheet(std::string,int duration = 100,bool loop = true,AnimatedSprite* owner = nullptr,double width = 0,double height = 0);
        sf::Sprite& getSprite();
        int getWaitTime();
        void reset();
        void update(bool orientation,int increment=1);
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        int duration;
        double width;
        double height;
        bool isLoop;
        int currFrame;
        int maxFrame;
        AnimatedSprite* owner;
};

#endif