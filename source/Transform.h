#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector3.h"

struct Transform {
	Vector3 position, scale;
	float x_angle, y_angle, z_angle;
	Transform();
};

#endif