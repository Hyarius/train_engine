#ifndef jgl_color_H
#define jgl_color_H

#include <iostream>
#include <string>

#define CALC(value) ((value % 256) / 255.0f)

struct Color
{
	float r;
	float g;
	float b;
	float a;

	Color();
	Color(float p_r, float p_g, float p_b, float p_a = 1.0f);
	Color(int p_r, int p_g, int p_b, int p_a = 255);

	float *decompose();
};

ostream& operator<<(ostream& os, const Color& value);

#endif
