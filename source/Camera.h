#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include "Vector3.h"
#include "TransformVectors.h"

/*
	Camera:
		class for projection matrix and view matrix processing
*/

class Camera {
private:
	glm::mat4 projection;
public:
	Vector3 position;
	Vector3 direction; 

	Camera(int width, int height);

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
};

#endif