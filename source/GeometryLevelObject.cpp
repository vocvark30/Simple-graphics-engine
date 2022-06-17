#include "GeometryLevelObject.h"

GeometryLevelObject::GeometryLevelObject(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray> vertexArray,
	const Camera& camera, const Geometry::objectGeometry& object) : 
	LevelObject(shader, vertexArray, camera), geometry(object), originalGeometry(object) { }

void GeometryLevelObject::updateGeometry() {
	glm::mat4 inverse = glm::transpose(glm::inverse(modelMatrix));

	for (int i = 0; i < originalGeometry.triangles.size(); i++) {
		geometry.triangles[i].v1 = 
			transformToVector3(modelMatrix * transformToVec4(originalGeometry.triangles[i].v1));
		geometry.triangles[i].v2 = 
			transformToVector3(modelMatrix * transformToVec4(originalGeometry.triangles[i].v2));
		geometry.triangles[i].v3 = 
			transformToVector3(modelMatrix * transformToVec4(originalGeometry.triangles[i].v3));
		geometry.triangles[i].n = 
			transformToVector3(inverse * transformToVec4(originalGeometry.triangles[i].n)).normalize();
	}

	for (int i = 0; i < originalGeometry.lineSegments.size(); i++) {
		geometry.lineSegments[i].v1 = 
			transformToVector3(modelMatrix * transformToVec4(originalGeometry.lineSegments[i].v1));
		geometry.lineSegments[i].v2 = 
			transformToVector3(modelMatrix * transformToVec4(originalGeometry.lineSegments[i].v2));

		for (int j = 0; j < originalGeometry.lineSegments[i].normalVectors.size(); j++) {
			geometry.lineSegments[i].normalVectors[j] = 
				transformToVector3(inverse * transformToVec4(originalGeometry.lineSegments[i].normalVectors[j])).normalize();
		}
	}
}