#include "Camera.h"


Camera::Camera(int width, int height) {
	position = Vector3();
	direction = Vector3();
	projection = glm::perspective(45.0f, (float)width/height, 0.1f, 100.0f);
}

glm::mat4 Camera::GetViewMatrix() const {
	glm::vec3 pos = transformToVec3(position);
	glm::vec3 dir = transformToVec3(position + direction);

	glm::mat4 view = glm::lookAt(pos, dir, transformToVec3(Vector3::up));
	return view;
}

glm::mat4 Camera::GetProjectionMatrix() const {
	return projection;
}