#include "uiNode.hpp"
#include "engine.hpp"
UINode::UINode() : Node("UI"){
    offset.x = offset.y = 0;
}

void UINode::setPosition(sf::Vector2f position){
    offset = position;
}
void UINode::setPosition(double x,double y){
    offset.x = x;
    offset.y = y;
}
void UINode::refresh(){
    this->position.x = offset.x + Engine::engine()->getView()->getCenter().x - Engine::engine()->getView()->getSize().x/2;
    this->position.y = offset.y + Engine::engine()->getView()->getCenter().y - Engine::engine()->getView()->getSize().y/2;
}