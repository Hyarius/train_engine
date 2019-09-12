#include "engine.h"

c_map::c_map(string path, c_widget *parent) : c_widget(parent)
{
	_map = c_image(path);
	_map_anchor = _map.size() / -2;
	_zoom = 1.0f;
	_selected = nullptr;
	_cities.clear();
}

void c_map::render()
{
	_viewport->use();
	_viewport->clear();

	_map.draw(_viewport, _map_anchor + size() / 2.0f, _map.size() * _zoom);

	for (size_t i = 0; i < _cities.size(); i++)
		_cities[i]->draw();
}

bool c_map::handle_keyboard()
{
	return (false);
}

void c_map::select_city(c_city *city)
{
	_selected = city;
}

Vector2 c_map::convert_to_map_coord(Vector2 source)
{
	return (((source - _viewport->anchor()) - (_map_anchor + size() / 2.0f)) / _zoom);
}

void c_map::add_city()
{
	Vector2 pos = convert_to_map_coord(g_mouse->pos);

	c_city *new_city = new c_city(this, pos);
	//select_city(new_city);
	_cities.push_back(new_city);
	//new_city->select();
}

c_city *c_map::check_city()
{
	for (size_t i = 0; i < _cities.size(); i++)
		if (_cities[i]->clicked(g_mouse->pos) == true)
			return (_cities[i]);

	return (nullptr);
}

bool c_map::handle_mouse()
{
	if (is_pointed(g_mouse->pos))
	{
		if (g_mouse->get_button(MOUSE_LEFT) == MOUSE_DOWN)
		{
			if (g_mouse->rel_pos != Vector2(0, 0))
			{
				_map_anchor = _map_anchor + g_mouse->rel_pos;
				return (true);
			}
		}
		if (g_mouse->get_button(MOUSE_LEFT) == MOUSE_UP)
		{
			if (g_mouse->motion == false)
			{
				if (_selected == nullptr)
				{
					c_city *result = check_city();
					if (result == nullptr)
						add_city();
					else
						select_city(result);
				}
				else
				{
					_selected->select();
					select_city(nullptr);
				}
				return (true);
			}
		}
	}

	if (g_mouse->wheel != 0)
	{
		float ratio_x;
		float ratio_y;

		ratio_x = (_map.size().x * _zoom) / _map_anchor.x;
		ratio_y = (_map.size().y * _zoom) / _map_anchor.y;

		if (g_mouse->wheel > 0)
			_zoom *= 1.2f;
		else
			_zoom *= 0.8f;

		_map_anchor.x = (_map.size().x * _zoom) / ratio_x;
		_map_anchor.y = (_map.size().y * _zoom) / ratio_y;

		return (true);

	}
	return (false);
}

float c_map::zoom()
{
	return (_zoom);
}

Vector2 c_map::map_anchor()
{
	return (_map_anchor);
}
