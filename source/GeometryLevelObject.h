#ifndef GEOMETRY_LEVEL_OBJECT_H
#define GEOMETRY_LEVEL_OBJECT_H

#include "LevelObject.h"
#include "Geometry.h"
#include "TransformVectors.h"

/*
	GeometryLevelObject inherited from LevelObject, used for geometry processing
*/

class GeometryLevelObject : public LevelObject {
protected:
	Geometry::objectGeometry originalGeometry; //Constant
public:
	Geometry::objectGeometry geometry;

	GeometryLevelObject(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray> vertexArray,
		const Camera& camera, const Geometry::objectGeometry& geometry);

	// Called when modelMatrix is changed
	// updateGeometry() changes geometry: triangles positions and normals
	void updateGeometry();
};

#endif