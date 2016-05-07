#include <glm/glm.hpp>

class Light 
{
public:
	Light(float intensity,
			   glm::vec3 position,
			   glm::vec3 color) 
		: intensity(intensity), position(position), color(color) {} 
	float intensity;
	glm::vec3 position;
	glm::vec3 color;
};

class PointLight : public Light 
{ 
public:
	PointLight(float intensity,
			   glm::vec3 position,
			   glm::vec3 color) 
		: Light(intensity, position, color) {} 
};