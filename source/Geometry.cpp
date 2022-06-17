#include "Geometry.h"

using namespace Geometry;

Geometry::triangle::triangle(const Vector3& a, const Vector3& b, const Vector3& c) :
	v1(a), v2(b), v3(c), n(Vector3::crossProduct(b - a, c - a).normalize()) { }

Geometry::lineIntersection::lineIntersection(bool i, const Vector3& p) : intersect(i), point(p) { }
Geometry::lineIntersection::lineIntersection() : lineIntersection(false, Vector3::zero) { }

bool lineSegment::operator==(const lineSegment& l) const {
	return ((v1 == l.v1) && (v2 == l.v2)) || ((v1 == l.v2) && (v2 == l.v1));
}

lineSegment::lineSegment(const Vector3& v1, const Vector3& v2) : v1(v1), v2(v2) { }

void updateLineSegments(std::vector<lineSegment>& lineSegments,
	const Vector3& add1, const Vector3& add2, const Vector3& v, const Vector3& triangleNormal) {
	lineSegment add(add1, add2);

	std::vector<lineSegment>::iterator it;
	it = std::find(lineSegments.begin(), lineSegments.end(), add);
	if (it == lineSegments.end()) {
		lineSegments.push_back(add);
		it = lineSegments.end() - 1;
	}

	Vector3 normal = Vector3::crossProduct(triangleNormal, add2 - add1);
	if (Vector3::dotProduct(v - add1, normal) > 0) {
		normal = normal * (-1.0f);
	}

	(*it).normalVectors.push_back(normal);
}

objectGeometry::objectGeometry(const std::vector<Vector3>& vertices, const std::vector<unsigned int>& indices) {
	if (indices.size() % 3 == 0) {
		for (size_t i = 0; i < (indices.size() / 3); i++) {
			Vector3 v1 = vertices[indices[i * 3]];
			Vector3 v2 = vertices[indices[i * 3 + 1]];
			Vector3 v3 = vertices[indices[i * 3 + 2]];
			triangles.push_back(triangle(v1, v2, v3));

			updateLineSegments(lineSegments, v1, v2, v3, triangles.back().n);
			updateLineSegments(lineSegments, v2, v3, v1, triangles.back().n);
			updateLineSegments(lineSegments, v3, v1, v2, triangles.back().n);


		}
	}
}

bool Geometry::pointInTriangle(const Vector3& v, const triangle& u) {
	Vector3 n1 = Vector3::crossProduct(u.v2 - u.v1, v - u.v1);
	Vector3 n2 = Vector3::crossProduct(u.v3 - u.v2, v - u.v2);
	Vector3 n3 = Vector3::crossProduct(u.v1 - u.v3, v - u.v3);

	return (Vector3::dotProduct(n1, n2) > 0) && (Vector3::dotProduct(n1, n3) > 0);
}

bool Geometry::pointOnVector(const Vector3& v1, const Vector3& v2, const Vector3& a) {
	return Vector3::dotProduct(a - v1, a - v2) <= 0;
}

lineIntersection Geometry::lineIntersect(const Vector3& v1, const Vector3& v2, const triangle& u) {
	float v2v1Projection = Vector3::dotProduct(v2 - v1, u.n);
	if (v2v1Projection != 0) {
		float distance = Vector3::dotProduct(u.n, u.v1 - v1);
		return lineIntersection(true, v1 + (v2 - v1) * (distance / v2v1Projection));
	} else {
		return lineIntersection(false, Vector3::zero);
	}
}


lineIntersection Geometry::lineTriangle(const Vector3& v1, const Vector3& v2, const triangle& u) {
	lineIntersection i = lineIntersect(v1, v2, u);
	if (i.intersect && pointInTriangle(i.point, u)) {
		return i;
	} else {
		return lineIntersection(false, Vector3::zero);
	}
}

lineIntersection Geometry::vectorTriangle(const Vector3& v1, const Vector3& v2, const triangle& u) {
	lineIntersection i = lineTriangle(v1, v2, u);
	if (i.intersect && pointOnVector(v1, v2, i.point)) {
		return i;
	} else {
		return lineIntersection(false, Vector3::zero);
	}
}


// length of direction should be 1; returns nearest to v1 point of intersection
lineIntersection Geometry::lineSphere(const Vector3& v1, const Vector3& direction, const Vector3& o, float r) {
	Vector3 v = v1 - o;

	float b = Vector3::dotProduct(direction, v);
	float D = b * b - (v.length2() - r * r);

	if (D >= 0) {
		D = std::sqrt(D);
		float d1 = -b + D;
		float d2 = -b - D;
		return lineIntersection(true, std::abs(d1) < std::abs(d2) ? v1 + direction * d1 : v1 + direction * d2);
	} else {
		return lineIntersection(false, Vector3::zero);
	}
}

Vector3 Geometry::pointToLineProjection(const Vector3& v1, const Vector3& v2, const Vector3& a) {
	Vector3 n = (v2 - v1).normalize();
	return v1 - n * Vector3::dotProduct(n, v1 - a);
}

Vector3 Geometry::pointToTriangleProjection(const Vector3& v, const triangle& u) {
	return v + u.n * (Vector3::dotProduct(u.n, u.v1 - v));
}

Vector3 Geometry::nearestPointOnVector(const Vector3& l1, const Vector3& l2, const Vector3& a) {
	Vector3 projection = pointToLineProjection(l1, l2, a);

	Vector3 nearestPoint;
	if (pointOnVector(l1, l2, projection)) {
		nearestPoint = projection;
	} else {
		nearestPoint = (a - l1).length2() < (a - l2).length2() ? l1 : l2;
	}

	return nearestPoint;
}

Vector3 Geometry::sphereToObject(const Vector3& v1, const Vector3& v2, const objectGeometry& object,
	float r, Vector3& add, int& count) {
	Vector3 sum;

	for (int i = 0; i < object.triangles.size(); i++) {
		Vector3 projection = pointToTriangleProjection(v2, object.triangles[i]);
		if ((v2 - projection).length2() < r * r) {
			if (pointInTriangle(projection, object.triangles[i])) {
				Vector3 n = object.triangles[i].n * r;
				if (Vector3::dotProduct(v1 - object.triangles[i].v1, n) < 0) {
					n = n * (-1.0f);
				}
				add += projection + n - v2;
				count++;
			}
		}
	}
	if (count > 0) {
		sum += add * (1.0f / count);
	}

	std::vector<Vector3> nearestPoints;
	for (int i = 0; i < object.lineSegments.size(); i++) {
		Vector3 toLine = object.lineSegments[i].v1 - v2;

		if (std::find_if(object.lineSegments[i].normalVectors.begin(), object.lineSegments[i].normalVectors.end(),
			[&toLine](const Vector3& v)
			{return Vector3::dotProduct(v, toLine) > 0.0f; }) == object.lineSegments[i].normalVectors.end()) {
			Vector3 nearestPoint = nearestPointOnVector(object.lineSegments[i].v1, object.lineSegments[i].v2, v2);
			if ((v2 - nearestPoint).length2() < r * r) {
				if (std::find(nearestPoints.begin(), nearestPoints.end(), nearestPoint) == nearestPoints.end()) {
					nearestPoints.push_back(nearestPoint);

					count++;
					add += (v2 - nearestPoint).normalize() * (r - (v2 - nearestPoint).length());
				}
			}
		}
	}
	if (!nearestPoints.empty()) {
		sum += add * (1.0f / nearestPoints.size());
	}
	return sum;
}