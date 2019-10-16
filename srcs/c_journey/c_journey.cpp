#include "engine.h"

c_journey::c_journey(c_map *p_map)
{
	_map = p_map;
	_path.clear();
	_schedule.clear();
}

void c_journey::add_point(c_milestone *new_point, pair_int new_point_shedule)
{
	_path.push_back(new_point);
	_schedule.push_back(new_point_shedule);
}

void c_journey::draw()
{
	if (_map == nullptr || _path.size() <= 1)
		return;

	for (size_t i = 0; i < _path.size() - 1; i++)
	{
		Vector2 pos1 = _map->convert_to_screen_coord(_path[i]->pos());
		Vector2 pos2 = _map->convert_to_screen_coord(_path[i + 1]->pos());

		draw_line(_map->viewport(), Color(255, 120, 0), pos1, pos2, 9);
	}
}
