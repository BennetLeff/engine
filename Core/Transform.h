/*
 * Transform.h
 *
 *  Created on: Apr 22, 2016
 *      Author: bennetleff
 */

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <QObject>

class Transform {
public:
	explicit Transform(const glm::vec3& pos = glm::vec3(),
			  const glm::vec3& rot = glm::vec3(),
			  const glm::vec3& scale = glm::vec3(1.0f)) :
	pos(pos),
	rot(rot),
	scale(scale) { }

	glm::mat4 getModel() const;

	void setPosition(const glm::vec3& modelPosition);
	void setRotation(const glm::vec3& modelRotation);
	void setScale(const glm::vec3& modelScale);

	glm::vec3* getPosition();
	glm::vec3* getRotation();
	glm::vec3* getScale();

private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
	glm::mat4 model;
};

#endif /* TRANSFORM_H_ */
