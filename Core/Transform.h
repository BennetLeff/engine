/*
 * Transform.h
 *
 *  Created on: Apr 22, 2016
 *      Author: bennetleff
 */

#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <QObject>

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

class Transform : public QObject
{
	Q_OBJECT

    Q_PROPERTY(Vec3* Rotation READ rotation)
    Q_PROPERTY(Vec3* Position READ position)
    Q_PROPERTY(Vec3* Scale READ scale)

public:
	Transform(const glm::vec3& pos = glm::vec3(),
			  const glm::vec3& rot = glm::vec3(),
			  const glm::vec3& scale = glm::vec3(1.0f)) :
    mPosition(pos), mRotation(rot), mScale(scale)
    { }

	glm::mat4 getModel() const;

	Vec3* position();
	Vec3* rotation();
	Vec3* scale();

private:
	Vec3 mPosition;
	Vec3 mRotation;
	Vec3 mScale;
	glm::mat4 model;
};