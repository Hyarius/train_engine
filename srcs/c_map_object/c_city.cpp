#include "engine.h"

#define CITY_SIZE 5.0f

c_city::c_city(Vector2 p_pos)
{
	_milestone = nullptr;
	_pos = p_pos;
	_name = "City";
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

bool c_city::is_here(Vector2 p_pos)
{
	Vector2 pos1, pos2, size1;

	size1 = CITY_SIZE;
	pos1 = _pos - size1 / 2;
	pos2 = pos1 + size1;
	if (p_pos.x < pos1.x || p_pos.x > pos2.x || p_pos.y < pos1.y || p_pos.y > pos2.y)
		return (false);
	return (true);
}

bool c_city::clicked(Vector2 mouse)
{

	Vector2 pos1, pos2, size1;

	size1 = CITY_SIZE * g_map->zoom() * _selected + CITY_SIZE;
	pos1 = g_map->anchor() + g_map->map_anchor() + g_map->area() / 2 + _pos * g_map->zoom() - size1 / 2;
	pos2 = pos1 + size1;
	if (mouse.x < pos1.x || mouse.x > pos2.x || mouse.y < pos1.y || mouse.y > pos2.y)
		return (false);
	return (true);
}

void c_city::draw()
{
	static Color select_color = Color(55, 55, 255);
	static Color unselect_color = Color(255, 55, 55);

	Vector2 pos1, size1;
	size1 = CITY_SIZE * g_map->zoom() * _selected;
	pos1 = g_map->convert_to_screen_coord(_pos);

	if (_pos != Vector2())
	{
		g_map->point_image()->draw((_selected == 1 ? 1 : 2), pos1 - size1/2, size1, g_map->viewport());
		//fill_centred_rectangle(g_map->viewport(), (_selected == 1 ? unselect_color : select_color), pos1, size1);
	}
}

void c_city::draw_name()
{
	Vector2 pos1, size1;
	size1 = CITY_SIZE * g_map->zoom() * _selected;
	pos1 = g_map->convert_to_screen_coord(_pos);

	if (_pos != Vector2() && _selected == 2)
	{
		int text_size = 8 * g_map->zoom();
		draw_centred_text(_name, pos1 + Vector2(0.0f, -size1.y * 1.5f), g_map->viewport(), text_size * 2, text_color::grey, text_style::bold);
	}
}
