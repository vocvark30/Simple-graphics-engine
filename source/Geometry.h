#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <vector>

#include "Vector3.h"

/*
	Geometry:
		contains all triangles intersection logic
*/

namespace Geometry {
	const float pi = std::acos(-1.0f);

	struct triangle {
		// vertices and normal
		Vector3 v1, v2, v3, n;

		// constructor takes 3 points and creates triangle
		triangle(const Vector3& a, const Vector3& b, const Vector3& c);
	};

	struct lineIntersection {
		bool intersect;
		Vector3 point;

		lineIntersection();
		lineIntersection(bool i, const Vector3& p);
	};

	struct lineSegment {
		Vector3 v1, v2;
		std::vector<Vector3> normalVectors; // vectors normal to lines, in triangles

		lineSegment(const Vector3& v1, const Vector3& v2);

		bool operator==(const lineSegment& l) const;
	};

	struct objectGeometry {
		std::vector<triangle> triangles;
		std::vector<lineSegment> lineSegments;

		objectGeometry(const std::vector<Vector3>& vertices, const std::vector<unsigned int>& indices);
	};

	bool pointInTriangle(const Vector3& v, const triangle& u);
	bool pointOnVector(const Vector3& v1, const Vector3& v2, const Vector3& a);

	lineIntersection lineIntersect(const Vector3& v1, const Vector3& v2, const triangle& u);
	lineIntersection lineTriangle(const Vector3& v1, const Vector3& v2, const triangle& u);
	lineIntersection vectorTriangle(const Vector3& v1, const Vector3& v2, const triangle& u);

	// length of direction should be 1; returns nearest to v1 point of intersection
	lineIntersection lineSphere(const Vector3& v1, const Vector3& direction, const Vector3& o, float r);

	Vector3 pointToLineProjection(const Vector3& v1, const Vector3& v2, const Vector3& a);
	Vector3 pointToTriangleProjection(const Vector3& v, const triangle& u);
	Vector3 nearestPointOnVector(const Vector3& l1, const Vector3& l2, const Vector3& a);

	Vector3 sphereToObject(const Vector3& v1, const Vector3& v2, const objectGeometry& object,
		float r, Vector3& add, int& sum);
}

#endif