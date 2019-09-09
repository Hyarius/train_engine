#include "engine.h"

#define CITY_SIZE 7.0f

int num = 0;

c_city::c_city(c_map *p_map, Vector2 p_pos)
{
	map = p_map;
	pos = p_pos;
	name = "City " + to_string(num);
	num++;
	selected = 1;
	Vector2 tmp = Vector2(350, 300);
}

void c_city::draw()
{
	static Color select_color = Color(55, 55, 255);
	static Color unselect_color = Color(255, 55, 55);

	if (map == nullptr)
		return ;

	Vector2 pos1, size1;
	size1 = CITY_SIZE * map->zoom() * selected;
	pos1 = map->map_anchor() + map->size() / 2 + pos * map->zoom();

	if (pos != Vector2())
	{
		int text_size = 8 * map->zoom();
		draw_centred_text(map->viewport(), name, pos1 + Vector2(0.0f, - size1.y * 1.5f), text_size, BLACK, BOLD);
		fill_centred_rectangle(map->viewport(), (selected == 1 ? unselect_color : select_color), pos1, size1);
	}
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
