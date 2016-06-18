//
// Created by bennet on 6/18/16.
//

#include "Core/Light.h"

Light::Light(float intensity,
             Vec3* position,
             Vec3* color)
    : intensity(intensity), position(position), color(color) {}