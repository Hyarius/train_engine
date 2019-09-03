#include "jgl.h"

c_viewport::c_viewport(c_color p_color, Vector2 p_anchor, Vector2 p_size)
{
	if (main_window == nullptr)
		main_window = new c_window("Main window");

	_renderer = main_window->renderer();
	_background = p_color;

	set_viewport(p_anchor, p_size);
}

void c_viewport::set_viewport(Vector2 p_anchor, Vector2 p_size)
{
	_anchor = p_anchor;
	_size = p_size;

	if (_anchor == Vector2())
		_anchor = Vector2(0, 0);
	if (_size == Vector2())
		_size = main_window->size();
}

void c_viewport::resize(Vector2 p_anchor, Vector2 p_size)
{
	_anchor = p_anchor;
	_size = p_size;
}

SDL_Renderer *c_viewport::renderer()
{
	return (_renderer);
}

Vector2 c_viewport::size()
{
	return (_size);
}

Vector2 c_viewport::anchor()
{
	return (_anchor);
}

void c_viewport::set_background(c_color p_color)
{
	_background = p_color;
}

void c_viewport::viewport()
{
	SDL_Rect rect = {_anchor.x, _anchor.y, _size.x, _size.y};
	SDL_RenderSetViewport(_renderer, &rect);
}

void c_viewport::set_c_color(c_color c_color)
{
	SDL_SetRenderDrawColor(_renderer, c_color.r * 255, c_color.g * 255, c_color.b * 255, c_color.a * 255);
}

void c_viewport::clear()
{
	viewport();
	set_c_color(_background);

	SDL_Rect rect = {0, 0, _size.x, _size.y};
	SDL_RenderFillRect(_renderer, &rect);
}
