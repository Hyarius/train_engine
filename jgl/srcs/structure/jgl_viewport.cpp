#include "jgl.h"

c_viewport::c_viewport(Color p_color, Vector2 p_anchor, Vector2 p_size)
{
	if (g_application == nullptr)
		g_application = new c_application("Main window");

	_renderer = g_application->renderer();
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
		_size = g_application->size();
}

void c_viewport::resize(Vector2 p_anchor, Vector2 p_size)
{
	_anchor = p_anchor;
	_size = p_size;
}

void c_viewport::use()
{
	if (_size.x <= 0 || _size.y <= 0)
		return ;

	SDL_Rect rect = {
			static_cast<int>(_anchor.x), static_cast<int>(_anchor.y),
			static_cast<int>(_size.x), static_cast<int>(_size.y)
		};

	SDL_RenderSetViewport(_renderer, &rect);
}

void c_viewport::set_Color(Color Color)
{
	SDL_SetRenderDrawColor(_renderer, Color.r * 255, Color.g * 255, Color.b * 255, Color.a * 255);
}

void c_viewport::clear()
{
	use();
	set_Color(_background);

	SDL_Rect rect = {
			static_cast<int>(0), static_cast<int>(0),
			static_cast<int>(_size.x), static_cast<int>(_size.y)
		};
	SDL_RenderFillRect(_renderer, &rect);
}
