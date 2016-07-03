#pragma once

#include <QObject>

#include "Core/GameObject.h"
#include "Core/Vec3.h"

class Light : public GameObject
{
    Q_OBJECT
    Q_PROPERTY(double Intensity MEMBER intensity)
    Q_PROPERTY(Vec3* Position MEMBER position)
    Q_PROPERTY(Vec3* Color MEMBER color)

public:
	Light(float intensity,
			   Vec3* position,
			   Vec3* color);

    float intensity;
	Vec3* position;
	Vec3* color;
};

class PointLight : public Light
{
public:
	PointLight(float intensity,
			   Vec3* position,
			   Vec3* color)
		: Light(intensity, position, color) {}

private:
	const short mMaxIntensity = 1;
	const short mMaxColorValue = 256;
};