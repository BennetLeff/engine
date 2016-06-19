//
// Created by bennet on 6/18/16.
//

#pragma once

#include <QObject>
#include <glm/glm.hpp>

class Vec3 : public QObject, public glm::vec3
{
    Q_OBJECT
    Q_PROPERTY(double x READ getX WRITE setX)
    Q_PROPERTY(double y READ getY WRITE setY)
    Q_PROPERTY(double z READ getZ WRITE setZ)
public:
    Vec3(double x = 0.0, double y = 0.0, double z = 0.0)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // Copy constructor
    Vec3(const Vec3& vector)
    {
        this->x = vector.x;
        this->y = vector.y;
        this->z = vector.z;
    }

    Vec3(glm::vec3 vector)
    {
        this->x = vector.x;
        this->y = vector.y;
        this->z = vector.z;
    }

private:
    double getX() { return this->x; }
    double getY() { return this->y; }
    double getZ() { return this->z; }

    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    void setZ(double z) { this->z = z; }
};
