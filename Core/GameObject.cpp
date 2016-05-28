//
// Created by bennet on 5/28/16.
//

#include "GameObject.h"

GameObject::GameObject()
{

}

std::string& GameObject::getName()
{
    return name;
}

void GameObject::setName(std::string name)
{
    this->name = name;
}

glm::vec3& GameObject::getPosition()
{
    return this->position;
}

void GameObject::setPosition(glm::vec3 position)
{
    this->position = position;
}
