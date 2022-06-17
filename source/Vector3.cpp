#include "Vector3.h"

const float Vector3::pi = std::acos(-1);
const float Vector3::e = 0.000001f;

const Vector3 Vector3::up = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::zero = Vector3(0.0f, 0.0f, 0.0f);

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) { }

Vector3::Vector3(float in_x, float in_y, float in_z) :
	x(in_x), y(in_y), z(in_z)  { }

Vector3 Vector3::operator+(const Vector3& v) const {
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const {
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator*(const float& f) const {
	return Vector3(x * f, y * f, z * f);
}

Vector3& Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

bool Vector3::operator==(const Vector3& v) const {
	return (std::abs(x - v.x) < e) && (std::abs(y - v.y) < e) && (std::abs(z - v.z) < e);
}

bool Vector3::operator!=(const Vector3& v) const {
	return !(*this == v);
}

Vector3& Vector3::rotate(const Vector3& axis, float a) {
	Vector3 result;
	float s = std::sin(a);
	float c = std::cos(a);
	result.x = x * (c + (1 - c) * axis.x * axis.x)
			 + y * ((1 - c) * axis.y * axis.x + s * axis.z)
			 + z * ((1 - c) * axis.z * axis.x - s * axis.y);
	result.y = x * ((1 - c) * axis.x * axis.y - s * axis.z)
			 + y * (c + (1 - c) * axis.y * axis.y)
			 + z * ((1 - c) * axis.z * axis.y + s * axis.x);
	result.z = x * ((1 - c) * axis.x * axis.z + s * axis.y)
			 + y * ((1 - c) * axis.y * axis.z - s * axis.x)
			 + z * (c + (1 - c) * axis.z * axis.z);

	x = result.x;
	y = result.y;
	z = result.z;

	return *this;
}

Vector3& Vector3::normalize() {
	float len = length();
	if (len > 0) {
		x = x / len;
		y = y / len;
		z = z / len;
	}
	return *this;
}

float Vector3::length() const {
	return std::sqrt(x * x + y * y + z * z);
}

float Vector3::length2() const {
	return x * x + y * y + z * z;
}

float Vector3::angle(const Vector3& v) const {
	float l = length() * v.length();

	if (l <= 0) {
		return 0.0f;
	}

	float d = dotProduct(*this, v) / l;
	if (d > 1.0f) {
		return 0.0f;
	} else if (d < -1.0f) {
		return pi;
	} else {
		return std::acos(d);
	}
}

float Vector3::dotProduct(const Vector3& v1, const Vector3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3::crossProduct(const Vector3& v1, const Vector3& v2) {
	return Vector3(	v1.y * v2.z - v1.z * v2.y,
					v1.z * v2.x - v1.x * v2.z,
					v1.x * v2.y - v1.y * v2.x);
}