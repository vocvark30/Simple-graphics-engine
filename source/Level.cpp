#include "Level.h"

Level::Level(int width, int height, inputData& input) :
	camera(width, height), input(input), width(width), height(height){

	camera.direction = Vector3(0.0f, 0.0f, -1.0f).normalize();

	camera.position.x = 6.0f;
	camera.position.y = 0.0f;
	camera.position.z = 0.0f;

	loadObjects();
}

void Level::loadObjects() {
	geometryStructure geometry = FileInput::readObject("res/objects/cube.obj");
	
	std::shared_ptr<Shader> shader = std::shared_ptr<Shader>(
		new Shader(FileInput::getString("res/shaders/texture.vertexshader"),
		FileInput::getString("res/shaders/texture.fragmentshader"), "res/textures/wall1.png"));

	std::shared_ptr<Shader> shader2 = std::shared_ptr<Shader>(
		new Shader(FileInput::getString("res/shaders/texture.vertexshader"),
			FileInput::getString("res/shaders/texture2.fragmentshader"), "res/textures/wall.png"));

	std::shared_ptr<VertexArray> vertexArray = std::shared_ptr<VertexArray>(
		new VertexArray(geometry.drawingVertices, geometry.drawingIndices, std::vector<int>{ 3, 2, 3 }));

	geometryObjects.push_back(
		std::shared_ptr<GeometryLevelObject>(
			new GeometryLevelObject
			(shader, vertexArray, camera, Geometry::objectGeometry(geometry.vertices, geometry.indices))
		));
	levelObjects.push_back(geometryObjects.back());
	levelObjects.back()->transform.scale = Vector3(10, 10, 10);
	levelObjects.back()->transform.position = Vector3(0, -12, 0);

	geometryObjects.push_back(
		std::shared_ptr<GeometryLevelObject>(
			new GeometryLevelObject
			(shader, vertexArray, camera, Geometry::objectGeometry(geometry.vertices, geometry.indices))
			));
	levelObjects.push_back(geometryObjects.back());

	levelObjects.back()->transform.x_angle = Geometry::pi / 4;
	levelObjects.back()->transform.z_angle = Geometry::pi / 4;

	geometryObjects.push_back(
		std::shared_ptr<GeometryLevelObject>(
			new GeometryLevelObject
			(shader2, vertexArray, camera, Geometry::objectGeometry(geometry.vertices, geometry.indices))
		));

	levelObjects.push_back(geometryObjects.back());
	levelObjects.back()->transform.position.y -= 1.85f;
	levelObjects.back()->transform.scale.y = 0.1f;
}

void Level::Update(long time) {
	dt = time / 1000000.0f;

	dx = (input.mouse_x - mouse_x) / width;
	dy = (input.mouse_y - mouse_y) / height;

	mouse_x = input.mouse_x;
	mouse_y = input.mouse_y;

	levelObjects[1]->transform.y_angle += 0.4f * dt;
	levelObjects.back()->transform.y_angle += 0.4f * dt;

	Movement(dt);
}

void Level::Movement(float dt) {
	camera.direction.rotate(Vector3::up, dx * rotationVelocity);
	

	float verticalAngleOffset = -(float)dy * rotationVelocity;
	if (verticalAngle + verticalAngleOffset > (Geometry::pi / 2) - boundAngle) {
		verticalAngleOffset = (Geometry::pi / 2) - boundAngle - verticalAngle;
	} else if (verticalAngle + verticalAngleOffset < -(Geometry::pi / 2) + boundAngle) {
		verticalAngleOffset = -(Geometry::pi / 2) + boundAngle - verticalAngle;
	}

	verticalAngle += verticalAngleOffset;
	camera.direction.rotate(Vector3::crossProduct(Vector3::up, camera.direction).normalize(), verticalAngleOffset);


	Vector3 direction;

	if (input.keys["w"]) {
		direction += camera.direction;
	} else if (input.keys["s"]) {
		direction += camera.direction * (-1.0f);
	}

	if (input.keys["d"]) {
		direction += Vector3::crossProduct(camera.direction, Vector3::up).normalize();
	} else if (input.keys["a"]) {
		direction += Vector3::crossProduct(camera.direction, Vector3::up).normalize() * (-1.0f);
	}

	if (direction.length2() > 0) {
		Vector3 directionProjection(direction.x, 0.0f, direction.z);
		directionProjection.normalize();

		velocity += directionProjection * (acceleration * dt);

		if (velocity.length() > maxVelocity * dt) {
			velocity.normalize();
			velocity = velocity * maxVelocity * dt;
		}
	} else {
		Vector3 newVelocity = velocity * (1.0f - acceleration * 10.0f * dt);
		if (Vector3::dotProduct(velocity, newVelocity) < 0.0f) {
			velocity = Vector3::zero;
		} else {
			velocity = newVelocity;
		}
	}

	if (onGround) {
		gravityVelocity = staticGravityVelocity;
	} else {
		gravityVelocity += gravityAcceleration * dt;
		if (gravityVelocity < -maxGravityVelocity) {
			gravityVelocity = -maxGravityVelocity;
		}
	}

	if (input.keys["space"] && onGround) {
		gravityVelocity += jumpAcceleration;
	}
	onGround = false;

	// movement
	Vector3 sum; // sum of all offsets from intersections
	int iteration = 0; // current iteration

	// varying while checking intersections
	Vector3 end = camera.position + Vector3(0.0f, gravityVelocity, 0.0f) + velocity; 
	do {
		sum = Vector3::zero;
		int count = 0;
		iteration++;

		for (int i = 0; i < geometryObjects.size(); i++) {
			Vector3 v = Geometry::sphereToObject(camera.position, end, geometryObjects[i]->geometry, r, sum, count);
		}

		if (Vector3::dotProduct(sum, Vector3::up) > 0.0f) {
			onGround = true;
		}

		if (count > 0) {
			end += sum * (1.0f / count);
		}
	} while ((sum != Vector3::zero) && (iteration < maxIteration));
	camera.position = end;
}

void Level::Draw() {
	for (int i = 0; i < levelObjects.size(); i++) {
		levelObjects[i]->CalculateModelMatrix();
		levelObjects[i]->Draw();
	}

	for (int i = 0; i < geometryObjects.size(); i++) {
		geometryObjects[i]->updateGeometry();
	}
}