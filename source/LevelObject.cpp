#include "LevelObject.h"

LevelObject::LevelObject(const std::shared_ptr<Shader>& shader, 
	const std::shared_ptr<VertexArray> vertexArray, const Camera& camera) :
	transform(), shader(shader), vertexArray(vertexArray), camera(camera) {

	matrixLocation = shader->GetUniformLocation("transformMatrix");
	modelMatrix = glm::mat4(1.0f);
}

void LevelObject::CalculateModelMatrix() {
	modelMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, transformToVec3(transform.position));

	modelMatrix = glm::rotate(modelMatrix, transform.x_angle, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, transform.y_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, transform.z_angle, glm::vec3(0.0f, 0.0f, 1.0f));

	modelMatrix = glm::scale(modelMatrix, transformToVec3(transform.scale));
}

void LevelObject::Draw() const {
	glm::mat4 resultMatrix = camera.GetProjectionMatrix() * camera.GetViewMatrix() * modelMatrix;

	shader->Bind();

	shader->SetMatrix(matrixLocation, resultMatrix);
	vertexArray->Draw();

	shader->Unbind();
}

LevelObject::~LevelObject() {}