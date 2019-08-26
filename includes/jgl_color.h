#ifndef JGL_COLOR_H
#define JGL_COLOR_H

#include <iostream>  
#include <string>

#define CALC(value) ((value % 256) / 255.0f)

struct Color
{
	float r;
	float g;
	float b;
	float a;

	Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
	Color(float p_r, float p_g, float p_b, float p_a = 1.0f) : r(p_r), g(p_g), b(p_b), a(p_a) {}
	Color(int p_r, int p_g, int p_b, int p_a = 255) : r(CALC(p_r)), g(CALC(p_g)), b(CALC(p_b)), a(CALC(p_a)) {}

	float *decompose() { return (&a); }
};

ostream& operator<<(ostream& os, const Color& value)
{
	os << "(r : " << to_string(value.r) << " / g : " << to_string(value.g) << " / b : " << to_string(value.b) << " / a : " << to_string(value.a) << ")";
	return os;
}

#endif