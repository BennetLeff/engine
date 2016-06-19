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
#include <glm/gtc/type_ptr.hpp>
#include "Core/Vec3.h"

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