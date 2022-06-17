#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include <vector>
#include <algorithm>
#include <memory>

#include "LevelObject.h"
#include "GeometryLevelObject.h"
#include "Geometry.h"
#include "FileInput.h"
#include "InputData.h"

/*
	Level:
		Central class
		- process input, draw objects, manage physics.
		- Draw() and Update() are called from outside
*/

class Level {
private:
	// Main camera 
	Camera camera;

	// Current velocity of player
	Vector3 velocity;

	// Vertical angle used for bounding
	float verticalAngle = 0.0f;

	// Current velocity of gravity acceleration, starts with staticGravityVelocity
	float gravityVelocity = 0.0f;

	// Physics constants
	const float maxGravityVelocity = 0.25f;
	const float gravityAcceleration = -0.2f;
	const float staticGravityVelocity = -0.01f;
	const float jumpAcceleration = 0.06f;
	const float maxVelocity = 2.0f;
	const float acceleration = 2.0f;
	const float rotationVelocity = 2.0f;

	// max count of iterations to check intersections
	const int maxIteration = 16;

	// Bound vertical angle to avoid rotation over 180 degrees
	const float boundAngle = Geometry::pi / 24;

	// Sphere radius of player approximation
	float r = 0.3f;

	// Used to check whether player can jump now or not
	bool onGround = false;

	// Used to calculate mouse position change per frame
	double mouse_x, mouse_y;

	// time change per frame
	float dt = 0.0f; 

	// mouse position change per frame
	float dx = 0.0f, dy = 0.0f; 

	// Size of window
	int width, height;

	// Struct for input handling, sets from outside
	inputData& input;

	std::vector<std::shared_ptr<LevelObject>> levelObjects;
	std::vector<std::shared_ptr<GeometryLevelObject>> geometryObjects;

	// Load resources from file system shaders, geometry of objects, textures
	void loadObjects();

	// Called from Update(), 
	void Movement(float dt);
public:
	// Load all vertex data, textures, shaders, transforms, create objects
	Level(int width, int height, inputData& input);

	void Update(long time);
	void Draw();
};

#endif