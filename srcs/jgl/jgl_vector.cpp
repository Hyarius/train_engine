#include "jgl.h"

using namespace std;

Vector3::Vector3(int p_value) : x(static_cast<float>(p_value)), y(static_cast<float>(p_value)), z(static_cast<float>(p_value))
{

}

Vector3::Vector3(float p_value) : x(p_value), y(p_value), z(p_value)
{

}

Vector3::Vector3(float p_x, float p_y, float p_z) : x(p_x), y(p_y), z(p_z)
{

}

Vector3::Vector3(int p_x, int p_y, int p_z) : x(static_cast<float>(p_x)), y(static_cast<float>(p_y)), z(static_cast<float>(p_z))
{

}

Vector3&		Vector3::operator = (int p_value) {
	x = static_cast<float>(p_value);
	y = static_cast<float>(p_value);
	z = static_cast<float>(p_value);
	return *this;
}

Vector3& Vector3::operator = (float  p_value) {
	x = p_value;
	y = p_value;
	z = p_value;
	return *this;
}

Vector3		Vector3::operator + (Vector3 delta)
{
	return (Vector3(this->x + delta.x, this->y + delta.y, this->z + delta.z));
}

Vector3		Vector3::operator - (Vector3 delta)
{
	return (Vector3(this->x - delta.x, this->y - delta.y, this->z - delta.z));
}

Vector3		Vector3::operator * (Vector3 delta)
{
	return (Vector3(this->x * delta.x, this->y * delta.y, this->z * delta.z));
}

Vector3		Vector3::operator / (Vector3 delta)
{
	return (Vector3(this->x / delta.x, this->y / delta.y, this->z / delta.z));
}

bool		Vector3::operator == (const Vector3& delta) const
{
	return ((this->x == delta.x && this->y == delta.y && this->z == delta.z) ? true : false);
}

bool		Vector3::operator != (const Vector3& delta) const
{
	return ((this->x == delta.x && this->y == delta.y && this->z == delta.z) ? false : true);
}

float *Vector3::decompose()
{
	return (&x);
}

Vector2::Vector2(int p_value) : x(static_cast<float>(p_value)), y(static_cast<float>(p_value))
{

}

Vector2::Vector2(float p_value) : x(p_value), y(p_value)
{

}

Vector2::Vector2(float p_x, float p_y) : x(p_x), y(p_y)
{

}

Vector2::Vector2(int p_x, int p_y) : x(static_cast<float>(p_x)), y(static_cast<float>(p_y))
{

}

Vector2&		Vector2::operator = (int p_value)
{
	x = static_cast<float>(p_value);
	y = static_cast<float>(p_value);
	return *this;
}

Vector2& Vector2::operator = (float  p_value)
{
	x = p_value;
	y = p_value;
	return *this;
}

Vector2		Vector2::operator + (Vector2 delta)
{
	return (Vector2(this->x + delta.x, this->y + delta.y));
}

Vector2		Vector2::operator - (Vector2 delta)
{
	return (Vector2(this->x - delta.x, this->y - delta.y));
}

Vector2		Vector2::operator * (Vector2 delta)
{
	return (Vector2(this->x * delta.x, this->y * delta.y));
}

Vector2		Vector2::operator / (Vector2 delta)
{
	return (Vector2(this->x / delta.x, this->y / delta.y));
}

bool		Vector2::operator == (const Vector2& delta) const
{
	return ((this->x == delta.x && this->y == delta.y) ? true : false);
}

bool		Vector2::operator != (const Vector2& delta) const
{
	return ((this->x == delta.x && this->y == delta.y) ? false : true);
}

float *Vector2::decompose()
{
	return (&x);
}
