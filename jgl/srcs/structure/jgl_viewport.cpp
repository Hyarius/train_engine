#include "jgl.h"

c_viewport::c_viewport(Color p_color, Vector2 p_anchor, Vector2 p_area)
{
	if (g_application == nullptr)
		g_application = new c_application("Main window");

	_renderer = g_application->renderer();
	_background = p_color;

	set_viewport(p_anchor, p_area);
}

void c_viewport::set_viewport(Vector2 p_anchor, Vector2 p_area)
{
	_anchor = p_anchor;
	_area = p_area;

	if (_anchor == Vector2())
		_anchor = Vector2(0, 0);
	if (_area == Vector2())
		_area = g_application->size();
}

void c_viewport::resize(Vector2 p_anchor, Vector2 p_area)
{
	_anchor = p_anchor;
	_area = p_area;
}

void c_viewport::use()
{
	if (_area.x <= 0 || _area.y <= 0)
		return ;

	SDL_Rect base_rect;

	SDL_RenderGetViewport(_renderer, &base_rect);

	Vector2 base_anchor = Vector2(base_rect.x, base_rect.y);
	Vector2 base_area = Vector2(base_rect.w, base_rect.h);

	Vector2 tmp_anchor = _anchor;
	Vector2 tmp_area = _area;

	cout << "-------------" << endl;
	cout << "Base : " << base_anchor << " / " << base_area << endl;
	cout << "tmp : " << tmp_anchor << " / " << tmp_area << endl;

	// if (_anchor.x < base_rect.x)
	// {
	// 	tmp_anchor.x = base_rect.x;
	// 	tmp_area.x += _anchor.x - base_rect.x;
	// }
	//
	// if (_anchor.y < base_rect.y)
	// {
	// 	tmp_anchor.y = base_rect.y;
	// 	tmp_area.y += _anchor.y - base_rect.y;
	// }

	SDL_Rect rect = {
			static_cast<int>(tmp_anchor.x), static_cast<int>(tmp_anchor.y),
			static_cast<int>(tmp_area.x), static_cast<int>(tmp_area.y)
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
			static_cast<int>(_area.x), static_cast<int>(_area.y)
		};
	SDL_RenderFillRect(_renderer, &rect);
}
