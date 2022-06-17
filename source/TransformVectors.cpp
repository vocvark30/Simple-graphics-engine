#include "TransformVectors.h"

glm::vec3 transformToVec3(const Vector3& v) {
	return glm::vec3(v.x, v.y, v.z);
}

glm::vec4 transformToVec4(const Vector3& v) {
	return glm::vec4(v.x, v.y, v.z, 1.0f);
}

Vector3 transformToVector3(const glm::vec4& v) {
	return Vector3(v.x, v.y, v.z);
}