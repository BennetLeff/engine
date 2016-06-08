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

class Transform : public QObject {
	Q_OBJECT
	Q_PROPERTY(double position_x READ getPosition_x)
	Q_PROPERTY(double position_y READ getPosition_y)
	Q_PROPERTY(double position_z READ getPosition_z)
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


    double getPosition_x() { return pos.x; }
    double getPosition_y() { return pos.y; }
    double getPosition_z() { return pos.z; }
    void setPosition_x(double x) { pos.x = x; }
    void setPosition_y(double y) { pos.y = y; }
    void setPosition_z(double z) { pos.z = z; }

};

#endif /* TRANSFORM_H_ */
