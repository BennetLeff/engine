//
// Created by bennet on 5/28/16.
//

#pragma once

#include <string>

#include <glm/glm.hpp>
#include <QtCore/QObject>

class GameObject // : public QObject
{
    // Q_OBJECT
public:
    GameObject();
    std::string& getName();
    void setName(std::string name);
    virtual glm::vec3& getPosition();
    virtual void setPosition(glm::vec3 position);
private:
    std::string name;
    glm::vec3 position;
};
