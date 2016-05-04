/*
 * Camera.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: bennetleff
 */
#include "Camera.h"
#include <stdio.h>

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
{
	// if window is resized this will need to be changed
	perspective_ = glm::perspective(fov, aspect, zNear, zFar);
	position_ = pos;
	forward_ = glm::vec3(0, 0, 1);
	up_ = glm::vec3(0, 1, 0);
}

glm::mat4 Camera::getProjection() const
{
	return perspective_ * glm::lookAt(position_, position_ + forward_, up_);
}

glm::vec3* Camera::getPosition()
{
    return &position_;
}