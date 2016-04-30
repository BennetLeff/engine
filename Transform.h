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


class Transform {
public:
	Transform(const glm::vec3& pos = glm::vec3(),
			  const glm::vec3& rot = glm::vec3(),
			  const glm::vec3& scale = glm::vec3(1.0f)) :
	pos_(pos),
	rot_(rot),
	scale_(scale) {}

	glm::mat4 getModel() const;

	void setPosition(const glm::vec3& modelPosition);
	void setRotation(const glm::vec3& modelRotation);
	void setScale(const glm::vec3& modelScale);

	glm::vec3* getPosition();
	glm::vec3* getRotation();
	glm::vec3* getScale();

private:
	glm::vec3 pos_;
	glm::vec3 rot_;
	glm::vec3 scale_;
	glm::mat4 model_;
};

#endif /* TRANSFORM_H_ */
