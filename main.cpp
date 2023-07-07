#include "engine.hpp"
#include "scenesCollection.hpp"
int main(int argc, char **argv)
{
    if (argc > 1)
    {
        std::string debugMode = argv[1];
        if (debugMode == "--debug")
        {
            Engine::engine()->setDebugMode(true);
        }
    }

    SceneCollection::loadScenes();

    Engine::engine()->start();

    delete Engine::engine();
    delete SceneManager::manager();
    return 0;
}