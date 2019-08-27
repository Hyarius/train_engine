#ifndef JGL_VIEWPORT_H
#define JGL_VIEWPORT_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_window.h"

extern class c_window *main_window;

class c_viewport
{
private:
	SDL_Renderer *_renderer;
	c_color _background;

	Vector2 _anchor;
	Vector2 _size;

public:
	c_viewport(c_color p_color = c_color(), Vector2 p_anchor = Vector2(), Vector2 p_size = Vector2())
	{
		if (main_window == nullptr)
			main_window = new c_window("Main window");

		_renderer = main_window->renderer();
		_background = p_color;

		set_viewport(p_anchor, p_size);
	}

	void set_viewport(Vector2 p_anchor = Vector2(), Vector2 p_size = Vector2())
	{
		_anchor = p_anchor;
		_size = p_size;

		if (_anchor == Vector2())
			_anchor = Vector2(0, 0);
		if (_size == Vector2())
			_size = main_window->size();
	}

	void resize(Vector2 p_anchor, Vector2 p_size)
	{
		_anchor = p_anchor;
		_size = p_size;
	}

	SDL_Renderer *renderer()
	{
		return (_renderer);
	}

	Vector2 size()
	{
		return (_size);
	}

	Vector2 anchor()
	{
		return (_anchor);
	}

	void set_background(c_color p_color = c_color(50, 50, 50))
	{
		_background = p_color;
	}

	void viewport()
	{
		SDL_Rect rect = {_anchor.x, _anchor.y, _size.x, _size.y};
		SDL_RenderSetViewport(_renderer, &rect);
	}

	void set_c_color(c_color c_color)
	{
		SDL_SetRenderDrawColor(_renderer, c_color.r * 255, c_color.g * 255, c_color.b * 255, c_color.a * 255);
	}

	void clear()
	{
		viewport();
		set_c_color(_background);

		SDL_Rect rect = {0, 0, _size.x, _size.y};
		SDL_RenderFillRect(_renderer, &rect);
	}
};

#endif
