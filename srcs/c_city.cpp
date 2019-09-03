#include "engine.h"

#define CITY_SIZE 7.0f

c_city::c_city(c_widget *p_parent, Vector2 p_pos) : c_frame(p_parent, 3, c_color(180, 180, 180), c_color(150, 150, 150))
{
	map = (c_map *)p_parent;
	pos = p_pos;
	selected = 1;
	Vector2 tmp = Vector2(350, 300);
	if (p_parent != NULL)
		set_geometry(Vector2(p_parent->size().x - tmp.x - 6.0f, 6.0f) , tmp);
	else
		set_geometry(Vector2(main_window->size().x - tmp.x - 6.0f, 6.0f), tmp);
}

void c_city::draw()
{
	static c_color select_color = c_color(55, 55, 255);
	static c_color unselect_color = c_color(255, 55, 55);
	if (map == nullptr)
		return ;


	Vector2 pos1, size1;
	size1 = CITY_SIZE * map->zoom() * selected;
	pos1 = map->map_anchor() + map->size() / 2 + pos * map->zoom() - size1 / 2;

	if (pos != Vector2())
		fill_rectangle(map->viewport(), (selected == 1 ? unselect_color : select_color), pos1, size1);
}

void c_city::select()
{
	selected = (selected == 1 ? 2 : 1);
}

bool c_city::clicked(Vector2 mouse)
{
	if (map == nullptr)
	{
		selected = 1;
		return false;
	}

	Vector2 pos1, pos2, size1;

	size1 = CITY_SIZE * map->zoom() * selected + CITY_SIZE;
	pos1 = map->anchor() + map->map_anchor() + map->size() / 2 + pos * map->zoom() - size1 / 2;
	pos2 = pos1 + size1;
	if (mouse.x < pos1.x || mouse.x > pos2.x || mouse.y < pos1.y || mouse.y > pos2.y)
	{
		selected = 1;
		return (false);
	}
	selected = 2;
	return (true);
}
