#include "engine.h"

c_journey::c_journey()
{
	_path.clear();
}

c_journey::~c_journey()
{
	for (size_t i = 0; i < _path.size(); i++)
		_path[i]->set_linked(false);
	for (size_t i = 0; i < _hour_panel.size(); i++)
		delete _hour_panel[i];
}

void c_journey::add_point(c_milestone *new_point, pair_int p_hour)
{
	static Vector2 panel_size = Vector2(150, 30);
	static Vector2 delta = Vector2(-panel_size.x / 2, 20.0f);
	_path.push_back(new_point);
	new_point->set_linked(true);

	if (new_point != nullptr && new_point->place() != nullptr)
	{
		c_hour_entry *new_hour = new c_hour_entry(p_hour.first, p_hour.second, g_map);
		new_hour->set_geometry(Vector2(g_map->convert_to_screen_coord(new_point->pos()) + delta), panel_size);
		new_hour->active();
		_hour_panel.push_back(new_hour);
	}
	else
		_hour_panel.push_back(nullptr);
}

void c_journey::actualize_panel()
{
	static Vector2 panel_size = Vector2(150, 30);
	static Vector2 delta = Vector2(-panel_size.x / 2, 20.0f);

	for (size_t i = 0; i < _hour_panel.size(); i++)
	{
		if (_hour_panel[i] != nullptr)
			_hour_panel[i]->set_geometry(Vector2(g_map->convert_to_screen_coord(_path[i]->pos()) + delta), panel_size);
	}
}

void c_journey::draw()
{
	if (_path.size() <= 1)
		return;

	for (size_t i = 0; i < _path.size() - 1; i++)
	{
		Vector2 pos1 = g_map->convert_to_screen_coord(_path[i]->pos());
		Vector2 pos2 = g_map->convert_to_screen_coord(_path[i + 1]->pos());

		draw_line(g_map->viewport(), Color(255, 120, 0), pos1, pos2, 9);
	}
}
