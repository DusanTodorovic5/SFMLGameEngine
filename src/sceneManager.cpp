#include "sceneManager.hpp"

SceneManager *SceneManager::instance = nullptr;

SceneManager::SceneManager()
{
    currScene = "emptyHolderScene";
    Scene *sc = new Scene();
    scenes.insert(std::pair<std::string, Scene *>(currScene, sc));
}
SceneManager *SceneManager::manager()
{
    if (instance == nullptr)
    {
        instance = new SceneManager();
    }
    return instance;
}
Scene *SceneManager::getCurrentScene()
{
    return scenes[currScene];
}
void SceneManager::switchScene(std::string newScene)
{
    if (currScene != newScene)
    {
        scenes[currScene]->focusChange(false);
        currScene = newScene;
        scenes[currScene]->focusChange(true);
        scenes[currScene]->start();
    }
}
void SceneManager::addScene(std::string name, Scene *scene)
{
    scenes.insert(std::pair<std::string, Scene *>(name, scene));
    scenes[name]->focusChange(false);
}
Node *SceneManager::getNodeByName(std::string name)
{
    return getCurrentScene()->getNodeByName(name);
}
int SceneManager::getNodeChildCount(std::string name)
{
    return getCurrentScene()->getNodeChildCount(name);
}
int SceneManager::getNodeChildCount(Node *node)
{
    return getCurrentScene()->getNodeChildCount(node);
}
void SceneManager::instantiate(Node *instance, Node *owner)
{
    getCurrentScene()->instantiate(instance, owner);
}
SceneManager::~SceneManager()
{
    for (std::pair<std::string, Scene *> n : scenes)
    {
        delete n.second;
    }
}
std::string SceneManager::getCurrentSceneName() const
{
    return currScene;
}