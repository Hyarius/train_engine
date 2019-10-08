#ifndef JGL_DRAW_PRIMITIVE_H
#define JGL_DRAW_PRIMITIVE_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_system.h"

using namespace std;

void draw_line(c_viewport *viewport, Color Color, Vector2 p1, Vector2 p2);
void draw_rectangle(c_viewport *viewport, Color Color, Vector2 pos, Vector2 size);
void fill_rectangle(c_viewport *viewport, Color Color, Vector2 pos, Vector2 size);
void draw_centred_rectangle(c_viewport *viewport, Color Color, Vector2 pos, Vector2 size);
void fill_centred_rectangle(c_viewport *viewport, Color Color, Vector2 pos, Vector2 size);
#endif
