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
	Color _background;

	Vector2 _anchor;
	Vector2 _size;

public:
	c_viewport(Color p_color = Color(), Vector2 p_anchor = Vector2(), Vector2 p_size = Vector2());

	void set_viewport(Vector2 p_anchor = Vector2(), Vector2 p_size = Vector2());

	void resize(Vector2 p_anchor, Vector2 p_size);

	void set_background(Color p_color = Color(50, 50, 50)){_background = p_color;}

	void use();

	void set_Color(Color Color);

	void clear();

	SDL_Renderer *renderer(){return (_renderer);}
	Vector2 &size(){return (_size);}
	Vector2 &anchor(){return (_anchor);}
};

#endif
