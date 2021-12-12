#include "scene.hpp"
#include <queue>
#include "collision.hpp"
#include <stack>
#include "uiNode.hpp"
Scene::Scene(){
    root = nullptr;
}
void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    levelOrderDraw(target,states);
}
void Scene::levelOrderDraw(sf::RenderTarget& target, sf::RenderStates states) const{
    if (!root){
        return;
    }
    SceneNode* head = root;
    std::queue<SceneNode*> queue;
    queue.push(head);       
    while (!queue.empty()){
        head = queue.front();
        queue.pop();
        if (head->node->getTag() == "UI"){
            ((UINode*)head->node)->refresh();
        }
        target.draw(*(head->node));
        for (SceneNode* node : head->children){
            queue.push(node);
        }
    }
}
Scene::SceneNode::SceneNode(Node* node){
    this->node = node;
}
void Scene::SceneNode::addChildren(struct SceneNode* sceneNode){
    this->children.push_back(sceneNode);
} 
void Scene::processInput(sf::Event::EventType type, sf::Event::KeyEvent key){
    if (!root){
        return;
    }
    SceneNode* head = root;
    std::queue<SceneNode*> queue;
    queue.push(head);
    while (!queue.empty()){
        head = queue.front();
        queue.pop();
        head->node->processInput(type,key);
        for (SceneNode* node : head->children){
            queue.push(node);
        }
    }
}
void Scene::update(){
    if (!root){
        return;
    }
    SceneNode* head = root;
    std::queue<SceneNode*> queue;
    queue.push(head);
    while (!queue.empty()){
        head = queue.front();
        queue.pop();
        head->node->update();
        for (SceneNode* node : head->children){
            queue.push(node);
        }
    }
}
void Scene::start(){
    if (!root){
        return;
    }
    SceneNode* head = root;
    std::queue<SceneNode*> queue;
    queue.push(head);
    while (!queue.empty()){
        head = queue.front();
        queue.pop();
        head->node->start();
        for (SceneNode* node : head->children){
            queue.push(node);
        }
    }
}
void Scene::checkCollision(){
    if (!root){
        return;
    }
    std::vector<Collision*> nodes;
    SceneNode* head = root;
    std::queue<SceneNode*> queue;
    queue.push(head);
    while (!queue.empty()){
        head = queue.front();
        queue.pop();
        //nodes.push_back(head->node);
        try{
            nodes.push_back((Collision*)(head->node->getComponent("Collision")));
        }
        catch (std::out_of_range){
            
        }
        for (SceneNode* node : head->children){
            queue.push(node);
        }
    }
    for (int i=0;i<nodes.size();i++){
        if (nodes[i]->getRigid()){
            for (int j=0;j<nodes.size();j++){
                if (nodes[i] != nodes[j]){
                    nodes[i]->checkCollision(*nodes[j]);
                }
            }
        }
    }
    for (int i=0;i<nodes.size();i++){
        nodes[i]->hadCollision();
    }
}
void Scene::focusChange(bool focus){
    if (!root){
        return;
    }
    SceneNode* head = root;
    std::queue<SceneNode*> queue;
    queue.push(head);
    while (!queue.empty()){
        head = queue.front();
        queue.pop();
        head->node->focusChange(focus);
        for (SceneNode* node : head->children){
            queue.push(node);
        }
    }
}
void Scene::applyMovement(){
    if (!root){
        return;
    }
    SceneNode* head = root;
    std::queue<SceneNode*> queue;
    queue.push(head);
    while (!queue.empty()){
        head = queue.front();
        queue.pop();
        head->node->applyVelocity();
        for (SceneNode* node : head->children){
            queue.push(node);
        }
    }
}
void Scene::setRoot(Scene::SceneNode* root){
    this->root = root;
}
void Scene::destroy(Node* node){
    if (std::find(forDestroy.begin(), forDestroy.end(),node) != forDestroy.end()){
        return;
    }
    forDestroy.push_back(node);

    
}
void Scene::lateDestroy(){
    for (Node* n : forDestroy){
        destroyInCollision(n);
        destroyInTree(n);
        delete n;
    }
    forDestroy.clear();
    for (Component* c : componentsForDestroy){
        delete c;
    }
    componentsForDestroy.clear();
}
void Scene::destroyInTree(Node* n){
    if (!root){
        return;
    }
    SceneNode* head = root;
    std::queue<SceneNode*> queue;
    queue.push(head);
    while (!queue.empty()){
        head = queue.front();
        queue.pop();
        for (SceneNode* node : head->children){
            if (n == node->node){
                for (SceneNode* children : node->children){
                    destroy(children->node);
                }
                head->children.erase(std::remove( head->children.begin(),  head->children.end(), node),  head->children.end());
                return;
            }
            queue.push(node);
        }
    }
}
void Scene::destroyInCollision(Node* n){
    if (!root){
        return;
    }
    SceneNode* head = root;
    std::queue<SceneNode*> queue;
    queue.push(head);
    while (!queue.empty()){
        head = queue.front();
        queue.pop();
        try{
            Collision* c = (Collision*)(head->node->getComponent("Collision"));
            c->destroyed(n);
        }
        catch (std::out_of_range){
            
        }
        for (SceneNode* node : head->children){
            queue.push(node);
        }
    }
}
Node* Scene::getNodeByName(std::string name){
    if (!root){
        return nullptr;
    }
    SceneNode* head = root;
    std::queue<SceneNode*> queue;
    queue.push(head);
    while (!queue.empty()){
        head = queue.front();
        queue.pop();
        if (head->node->getName() == name){
            return head->node;
        }
        for (SceneNode* node : head->children){
            queue.push(node);
        }
    }
    return nullptr;
}
int Scene::getNodeChildCount(std::string name){
    if (!root){
        return 0;
    }
    SceneNode* head = root;
    std::queue<SceneNode*> queue;
    queue.push(head);
    while (!queue.empty()){
        head = queue.front();
        queue.pop();
        if (head->node->getName() == name){
            return head->children.size();
        }
        for (SceneNode* node : head->children){
            queue.push(node);
        }
    }
    return 0;
}
int Scene::getNodeChildCount(Node* node){
    if (!root){
        return 0;
    }
    SceneNode* head = root;
    std::queue<SceneNode*> queue;
    queue.push(head);
    while (!queue.empty()){
        head = queue.front();
        queue.pop();
        if (head->node == node){
            return head->children.size();
        }
        for (SceneNode* node : head->children){
            queue.push(node);
        }
    }
    return 0;
}
void Scene::instantiate(Node* instance, Node* owner){
    if (!root){
        return;
    }
    SceneNode* head = root;
    std::queue<SceneNode*> queue;
    queue.push(head);
    while (!queue.empty()){
        head = queue.front();
        queue.pop();
        if (head->node == owner){
            head->addChildren(new SceneNode(instance));
            return;
        }
        for (SceneNode* node : head->children){
            queue.push(node);
        }
    }
    root->addChildren(new SceneNode(instance));
}
Scene::~Scene(){
    if (root == nullptr)
		return;
	SceneNode* p = root;
	std::stack<SceneNode*> stek;
	do {
		while (p != nullptr) {
            for (int i=1;i<p->children.size();i++){
                stek.push(p->children[i]);
            }
			stek.push(p);
			if (p->children.size() > 0){
                p = p->children[0];
            }else{
                p = nullptr;
            }
		}
		p = stek.top(); stek.pop();
        bool childrenInside = false;
        SceneNode* child = nullptr;
        if (!stek.empty())
        for (int i=0;i<p->children.size();i++){
            if (p->children[i] == stek.top()) {
                child = p->children[i];
                childrenInside = true;
                p->children.erase(p->children.begin() + i);
                break;
            }
        }
		if (!stek.empty() && childrenInside){
			stek.pop();
			stek.push(p);
			p = child;
		}
		else if (p){
			delete p->node;
            delete p;
			p = nullptr;
		}
	} while (!stek.empty());
}
void Scene::destroyComponent(Component* c){
    if (!(std::find(componentsForDestroy.begin(), componentsForDestroy.end(),c)!=componentsForDestroy.end()))
        componentsForDestroy.push_back(c);
}