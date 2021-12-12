#include "component.hpp"

std::string Component::getType() {
    return type;
}
Component::Component(std::string type) : type(type) { }

void Component::setType(std::string type) {
    this->type = type;
}