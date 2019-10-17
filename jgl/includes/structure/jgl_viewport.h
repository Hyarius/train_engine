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
	Vector2 _area;

public:
	c_viewport(Color p_color = Color(), Vector2 p_anchor = Vector2(), Vector2 p_size = Vector2());

	void set_anchor(Vector2 p_anchor){_anchor = p_anchor;}
	void set_area(Vector2 p_area){_area = p_area;}
	void set_viewport(Vector2 p_anchor = Vector2(), Vector2 p_area = Vector2());

	void resize(Vector2 p_anchor, Vector2 p_area);

	void set_background(Color p_color = Color(50, 50, 50)){_background = p_color;}

	void use();

	void set_Color(Color Color);

	void clear();

	SDL_Renderer *renderer(){return (_renderer);}
	Vector2 &area(){return (_area);}
	Vector2 &anchor(){return (_anchor);}
};

#endif
