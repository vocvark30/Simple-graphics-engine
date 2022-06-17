#ifndef TRANSFORM_VECTORS
#define TRANSFORM_VECTORS

#include <glm/glm.hpp>
#include "Vector3.h"

glm::vec3 transformToVec3(const Vector3& v);
glm::vec4 transformToVec4(const Vector3& v);
Vector3 transformToVector3(const glm::vec4& v);

#endif
