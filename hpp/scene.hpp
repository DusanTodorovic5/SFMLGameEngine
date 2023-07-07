#ifndef SCENE_CLASS
#define SCENE_CLASS

#include <SFML/Graphics.hpp>
#include <vector>
#include "node.hpp"
class Scene : public sf::Drawable
{
public:
    Scene();
    ~Scene();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void levelOrderDraw(sf::RenderTarget &target, sf::RenderStates states) const;
    void processInput(sf::Event::EventType, sf::Event::KeyEvent);
    void update();
    void start();
    void checkCollision();
    void focusChange(bool);
    void applyMovement();
    void destroy(Node *);
    struct SceneNode
    {
        SceneNode(Node *);
        void addChildren(struct SceneNode *);
        Node *node;
        std::vector<struct SceneNode *> children;
    } *root;
    void setRoot(Scene::SceneNode *);
    void lateDestroy();
    void destroyComponent(Component *);
    Node *getNodeByName(std::string);
    int getNodeChildCount(std::string);
    int getNodeChildCount(Node *);
    void instantiate(Node *instance, Node *owner);

private:
    void destroyInTree(Node *);
    void destroyInCollision(Node *);
    std::vector<Node *> forDestroy;
    std::vector<Component *> componentsForDestroy;
};

#endif