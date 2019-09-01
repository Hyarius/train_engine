#ifndef JGL_VIEWPORT_H
#define JGL_VIEWPORT_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_system.h"

class c_viewport
{
private:
	SDL_Renderer *_renderer;
	c_color _background;

	Vector2 _anchor;
	Vector2 _size;

public:
	c_viewport(c_color p_color = c_color(), Vector2 p_anchor = Vector2(), Vector2 p_size = Vector2());

	void set_viewport(Vector2 p_anchor = Vector2(), Vector2 p_size = Vector2());

	void resize(Vector2 p_anchor, Vector2 p_size);

	void set_background(c_color p_color = c_color(50, 50, 50));

	void viewport();

	void set_c_color(c_color c_color);

	void clear();

	SDL_Renderer *renderer();
	Vector2 size();
	Vector2 anchor();
};

#endif
