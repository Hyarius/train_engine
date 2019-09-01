#include "jgl.h"

c_color::c_color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f)
{

}

c_color::c_color(float p_r, float p_g, float p_b, float p_a) : r(p_r), g(p_g), b(p_b), a(p_a)
{

}

c_color::c_color(int p_r, int p_g, int p_b, int p_a) : r(CALC(p_r)), g(CALC(p_g)), b(CALC(p_b)), a(CALC(p_a))
{

}


float *c_color::decompose()
{
	return (&a);
}
