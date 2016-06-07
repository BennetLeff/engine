//
// Created by bennet on 5/28/16.
//

#pragma once

#include <string>

#include <glm/glm.hpp>
#include <QtCore/QObject>

class GameObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getQStringName)

public:
    GameObject();
    std::string& getName();
    void setName(std::string name);
    glm::vec3* getPosition();
    void setPosition(glm::vec3 position);
    QString getQStringName() { return QString(getName().data()); }
private:
    std::string name;
    glm::vec3 position;
};
