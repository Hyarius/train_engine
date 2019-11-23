#ifndef JGL_DRAW_PRIMITIVE_H
#define JGL_DRAW_PRIMITIVE_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_system.h"

using namespace std;

void draw_point(Color p_color, Vector2 center, c_viewport *viewport = nullptr, int width = 1);
void draw_line(Color Color, Vector2 p1, Vector2 p2, c_viewport *viewport = nullptr, int width = 1);
void draw_rectangle(Color Color, Vector2 pos, Vector2 size, c_viewport *viewport = nullptr);
void fill_rectangle(Color Color, Vector2 pos, Vector2 size, c_viewport *viewport = nullptr);
void draw_centred_rectangle(Color Color, Vector2 pos, Vector2 size, c_viewport *viewport = nullptr);
void fill_centred_rectangle(Color Color, Vector2 pos, Vector2 size, c_viewport *viewport = nullptr);

#endif
