#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class Vector3 {
private :
	const static float pi;

	// precision for operator==(...)
	const static float e;
public :
	float x, y, z;

	Vector3();
	Vector3(float in_x, float in_y, float in_z);

	Vector3 operator+(const Vector3& v) const;
	Vector3 operator-(const Vector3& v) const;
	Vector3 operator*(const float& f) const;

	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);

	bool operator==(const Vector3& v) const;
	bool operator!=(const Vector3& v) const;

	// length of axis should be 1
	Vector3& rotate(const Vector3& axis, float a);
	Vector3& normalize();

	float length() const;
	float length2() const;
	float angle(const Vector3& v) const;

	static float dotProduct(const Vector3& v1, const Vector3& v2);
	static Vector3 crossProduct(const Vector3& v1, const Vector3& v2);

	static const Vector3 up;
	static const Vector3 zero;
};

#endif