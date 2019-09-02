#include "engine.h"

c_map::c_map(string path, c_widget *parent) : c_widget(parent)
{
	map = c_image(path);
	anchor = map.size() / -2;
	zoom = 1.0f;
}

void c_map::render()
{
	_viewport->clear();

	map.draw(_viewport, anchor + size() / 2.0f, map.size() * zoom);

	for (size_t i = 0; i < points.size(); i++)
		fill_rectangle(_viewport, c_color(255, 55, 55), anchor + size() / 2.0f + points[i] * zoom - (3.5f * zoom), 7.0f * zoom);

	for (size_t i = 0; i < _childrens.size(); i++)
		_childrens[i]->render();
}

void c_map::handle_keyboard()
{
	
}

void c_map::add_city()
{
	Vector2 pos = ((mouse->pos - _viewport->anchor()) - (anchor + size() / 2.0f)) / zoom;
	points.push_back(pos);
}

void c_map::handle_mouse()
{
	if (mouse->get_button(MOUSE_LEFT) == MOUSE_DOWN)
	{
		if (mouse->rel_pos != Vector2(0, 0))
			anchor = anchor + mouse->rel_pos;
	}
	if (mouse->get_button(MOUSE_LEFT) == MOUSE_UP)
	{
		if (mouse->motion == false)
			add_city();
	}
	if (mouse->wheel != 0)
	{
		float ratio_x;
		float ratio_y;

		ratio_x = (map.size().x * zoom) / anchor.x;
		ratio_y = (map.size().y * zoom) / anchor.y;

		if (mouse->wheel > 0)
			zoom *= 1.2f;
		else
			zoom *= 0.8f;

		anchor.x = (map.size().x * zoom) / ratio_x;
		anchor.y = (map.size().y * zoom) / ratio_y;


	}

}
