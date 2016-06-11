/*
 * Transform.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: bennetleff
 */

#include "Transform.h"

glm::mat4 Transform::getModel() const
{
    glm::mat4 posMatrix = glm::translate(mPosition);
	glm::mat4 rotXMatrix = glm::rotate(mRotation.x, glm::vec3(1, 0, 0));
	glm::mat4 rotYMatrix = glm::rotate(mRotation.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZMatrix = glm::rotate(mRotation.z, glm::vec3(0, 0, 1));
	glm::mat4 scaleMatrix = glm::scale(mScale);

	glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

	return posMatrix * rotMatrix * scaleMatrix;
}

Vec3* Transform::position()
{
	return &mPosition;
}

Vec3* Transform::rotation()
{
    return &mRotation;
}

Vec3* Transform::scale()
{
    return &mScale;
}
