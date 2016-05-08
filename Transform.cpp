/*
 * Transform.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: bennetleff
 */

#include "Transform.h"

glm::mat4 Transform::getModel() const
{
	glm::mat4 posMatrix = glm::translate(pos);
	glm::mat4 rotXMatrix = glm::rotate(rot.x, glm::vec3(1, 0, 0));
	glm::mat4 rotYMatrix = glm::rotate(rot.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZMatrix = glm::rotate(rot.z, glm::vec3(0, 0, 1));
	glm::mat4 scaleMatrix = glm::scale(scale);

	glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

	return posMatrix * rotMatrix * scaleMatrix;
}

void Transform::setPosition(const glm::vec3& modelPosition)
{
	pos = modelPosition;
}
void Transform::setRotation(const glm::vec3& modelRotation)
{
	rot = modelRotation;
}
void Transform::setScale(const glm::vec3& modelScale)
{
	scale = modelScale;
}

glm::vec3* Transform::getPosition()
{
	return &pos;
}

glm::vec3* Transform::getRotation()
{
	return &rot;
}

glm::vec3* Transform::getScale()
{
	return &scale;
}
