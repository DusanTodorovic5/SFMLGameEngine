#ifndef GAME_ENGINE_CLASS
#define GAME_ENGINE_CLASS
#include "SFML/Graphics.hpp"
#include "sceneManager.hpp"
class Engine{
    public:
        static Engine* engine();
        void start();
        bool debugMode();
        void setDebugMode(bool debug = true);
        sf::View* getView();
        sf::Vector2u getWindowSize() const;
        void setWindowSize(sf::Vector2u size);
    private:
        bool started;
        Engine();
        static Engine* instance;
        bool debug;
        sf::View* view;
        sf::RenderWindow window;

};

#endif