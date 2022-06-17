#ifndef LEVEL_OBJECT_H
#define LEVEL_OBJECT_H

#include <memory>

#include "glm/glm.hpp"

#include "TransformVectors.h"
#include "Transform.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"

/*
	Level object:
		base class for drawing objects

		- shader, vertex array and camera are pointers because it can be used in many LevelObject instances.
		- can be drawn
*/

class LevelObject {
protected:
	const Camera& camera;
	std::shared_ptr<VertexArray> vertexArray;
	std::shared_ptr<Shader> shader;

	unsigned int matrixLocation;
public:
	// Used to save matrix state between CalculateModelMatrix() and Draw()
	// also used in GeometryLevelObject to update triangles state
	glm::mat4 modelMatrix;

	// Describes position, rotation and scale of object
	Transform transform;

	LevelObject(const std::shared_ptr<Shader>& shader, 
		const std::shared_ptr<VertexArray> vertexArray, const Camera& camera);

	// There used transform: position, scale, rotation to calculate
	// Each call modelMatrix is calculated from scratch using transform
	void CalculateModelMatrix();

	// Calculate resultMatrix, set it to shader and call draw vertexArray
	void Draw() const;

	virtual ~LevelObject();
};

#endif