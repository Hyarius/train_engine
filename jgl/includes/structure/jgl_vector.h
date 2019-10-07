#ifndef JGL_VECTOR_H
#define JGL_VECTOR_H

using namespace std;

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3(int p_value);
	Vector3(float p_value = -1);
	Vector3(float p_x, float p_y, float p_z);
	Vector3(int p_x, int p_y, int p_z);

	Vector3& operator = (int p_value);
	Vector3& operator = (float  p_value);

	Vector3 operator + (const Vector3& delta);
	Vector3 operator - (const Vector3& delta);
	Vector3 operator * (const Vector3& delta);
	Vector3 operator / (const Vector3& delta);
	void operator += (const Vector3& delta);
	void operator -= (const Vector3& delta);
	void operator *= (const Vector3& delta);
	void operator /= (const Vector3& delta);
	bool operator == (const Vector3& delta) const;
	bool operator != (const Vector3& delta) const;
	float *decompose();
};

struct Vector2
{
	float x;
	float y;

	Vector2(int p_value);
	Vector2(float p_value = -1);
	Vector2(float p_x, float p_y);
	Vector2(int p_x, int p_y);

	Vector2& operator = (int p_value);
	Vector2& operator = (float  p_value);

	Vector2 operator + (const Vector2& delta);
	Vector2	operator - (const Vector2& delta);
	Vector2	operator * (const Vector2& delta);
	Vector2	operator / (const Vector2& delta);
	void operator += (const Vector2& delta);
	void operator -= (const Vector2& delta);
	void operator *= (const Vector2& delta);
	void operator /= (const Vector2& delta);
	bool operator == (const Vector2& delta) const;
	bool operator != (const Vector2& delta) const;
	float *decompose();
};

float vector2_distance(Vector2 point_a, Vector2 point_b);

ostream& operator<<(ostream& os, const Vector2& value);

ostream& operator<<(ostream& os, const Vector3& value);

#endif
