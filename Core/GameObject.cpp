//
// Created by bennet on 5/28/16.
//

#include "GameObject.h"

GameObject::GameObject()
{
    // qRegisterMetaType<std::string>("std::string");
}

std::string& GameObject::getName()
{
    return name;
}

void GameObject::setName(std::string name)
{
    this->name = name;
}