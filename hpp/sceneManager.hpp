#ifndef SCENE_MANAGER_CLASS
#define SCENE_MANAGER_CLASS
#include <map>
#include "scene.hpp"
class SceneManager
{
public:
    static SceneManager *manager();
    Scene *getCurrentScene();
    std::string getCurrentSceneName() const;
    void switchScene(std::string);
    void addScene(std::string, Scene *);
    Node *getNodeByName(std::string);
    int getNodeChildCount(std::string);
    int getNodeChildCount(Node *);
    void instantiate(Node *instance, Node *owner);
    ~SceneManager();

private:
    SceneManager();
    static SceneManager *instance;
    std::string currScene;
    std::map<std::string, Scene *> scenes;
};

#endif