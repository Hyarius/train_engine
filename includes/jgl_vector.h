#ifndef JGL_VECTOR_H
#define JGL_VECTOR_H

#include <iostream>
#include <string>

using namespace std;

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3(int p_value) : x(static_cast<float>(p_value)), y(static_cast<float>(p_value)), z(static_cast<float>(p_value)) {}
	Vector3(float p_value = -1) : x(p_value), y(p_value), z(p_value) {}
	Vector3(float p_x, float p_y, float p_z) : x(p_x), y(p_y), z(p_z) {}
	Vector3(int p_x, int p_y, int p_z) : x(static_cast<float>(p_x)), y(static_cast<float>(p_y)), z(static_cast<float>(p_z)) {}

	Vector3&		operator = (int p_value) {
		x = static_cast<float>(p_value);
		y = static_cast<float>(p_value);
		z = static_cast<float>(p_value);
		return *this;
	}
	Vector3& operator = (float  p_value) {
		x = p_value;
		y = p_value;
		z = p_value;
		return *this;
	}

	Vector3		operator + (Vector3 delta) {
		return (Vector3(this->x + delta.x, this->y + delta.y, this->z + delta.z));
	}
	Vector3		operator - (Vector3 delta) {
		return (Vector3(this->x - delta.x, this->y - delta.y, this->z - delta.z));
	}
	Vector3		operator * (Vector3 delta) {
		return (Vector3(this->x * delta.x, this->y * delta.y, this->z * delta.z));
	}
	Vector3		operator / (Vector3 delta) {
		return (Vector3(this->x / delta.x, this->y / delta.y, this->z / delta.z));
	}
	bool		operator == (const Vector3& delta) const {
		return ((this->x == delta.x && this->y == delta.y && this->z == delta.z) ? true : false);
	}
	bool		operator != (const Vector3& delta) const {
		return ((this->x == delta.x && this->y == delta.y && this->z == delta.z) ? false : true);
	}
	float *decompose() { return (&x); }
};

struct Vector2
{
	float x;
	float y;

	Vector2(int p_value) : x(static_cast<float>(p_value)), y(static_cast<float>(p_value)) {}
	Vector2(float p_value = -1) : x(p_value), y(p_value) {}
	Vector2(float p_x, float p_y) : x(p_x), y(p_y) {}
	Vector2(int p_x, int p_y) : x(static_cast<float>(p_x)), y(static_cast<float>(p_y)) {}

	Vector2&		operator = (int p_value) {
		x = static_cast<float>(p_value);
		y = static_cast<float>(p_value);
		return *this;
	}
	Vector2& operator = (float  p_value) {
		x = p_value;
		y = p_value;
		return *this;
	}

	Vector2		operator + (Vector2 delta) {
		return (Vector2(this->x + delta.x, this->y + delta.y));
	}
	Vector2		operator - (Vector2 delta) {
		return (Vector2(this->x - delta.x, this->y - delta.y));
	}
	Vector2		operator * (Vector2 delta) {
		return (Vector2(this->x * delta.x, this->y * delta.y));
	}
	Vector2		operator / (Vector2 delta) {
		return (Vector2(this->x / delta.x, this->y / delta.y));
	}
	bool		operator == (const Vector2& delta) const {
		return ((this->x == delta.x && this->y == delta.y) ? true : false);
	}
	bool		operator != (const Vector2& delta) const {
		return ((this->x == delta.x && this->y == delta.y) ? false : true);
	}
	float *decompose() { return (&x); }
};

ostream& operator<<(ostream& os, const Vector2& value)
{
	os << "(" << to_string(value.x) << " / " << to_string(value.y) << ")";
	return os;
}

ostream& operator<<(ostream& os, const Vector3& value)
{
	os << "(" << to_string(value.x) << " / " << to_string(value.y) << " / " << to_string(value.z) << ")";
	return os;
}

#endif
