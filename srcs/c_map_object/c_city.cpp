#include "engine.h"

#define CITY_SIZE 7.0f

int num = 0;

c_city::c_city(c_map *p_map, Vector2 p_pos)
{
	_milestone = nullptr;
	_map = p_map;
	_pos = p_pos;
	_name = "City " + to_string(num);
	_waiting_time = 5;
	num++;
	_selected = 1;
	Vector2 tmp = Vector2(350, 300);
}

c_city::~c_city()
{
	if (_milestone != nullptr)
		delete _milestone;
}

void c_city::select(bool state)
{
	_selected = (state == true ? 2 : 1);
}

bool c_city::clicked(Vector2 mouse)
{
	if (_map == nullptr)
		return false;

	Vector2 pos1, pos2, size1;

	size1 = CITY_SIZE * _map->zoom() * _selected + CITY_SIZE;
	pos1 = _map->anchor() + _map->map_anchor() + _map->size() / 2 + _pos * _map->zoom() - size1 / 2;
	pos2 = pos1 + size1;
	if (mouse.x < pos1.x || mouse.x > pos2.x || mouse.y < pos1.y || mouse.y > pos2.y)
		return (false);
	return (true);
}

void c_city::draw()
{
	static Color select_color = Color(55, 55, 255);
	static Color unselect_color = Color(255, 55, 55);

	if (_map == nullptr)
		return;

	Vector2 pos1, size1;
	size1 = CITY_SIZE * _map->zoom() * _selected;
	pos1 = _map->convert_to_screen_coord(_pos);

	if (_pos != Vector2())
	{
		fill_centred_rectangle(_map->viewport(), (_selected == 1 ? unselect_color : select_color), pos1, size1);
	}
}

void c_city::draw_name()
{
	if (_map == nullptr)
		return;

	Vector2 pos1, size1;
	size1 = CITY_SIZE * _map->zoom() * _selected;
	pos1 = _map->convert_to_screen_coord(_pos);

	if (_pos != Vector2())
	{
		int text_size = 8 * _map->zoom();
		draw_centred_text(_map->viewport(), _name, pos1 + Vector2(0.0f, -size1.y * 1.5f), text_size, text_color::grey, text_style::bold);
	}
}
