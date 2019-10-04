#include "engine.h"

void c_map::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	Vector2 button_size = Vector2(100, 30);
	Vector2 button_pos = this->size() - 5 - button_size;
	_calib_button->set_geometry(button_pos, button_size);

	_zoom = 1.0f;
	while (_map->size().x * _zoom < p_area.x)
		_zoom += 0.2f;

	_map_anchor = (_map->size() * _zoom) / -2;

	Vector2 panel_anchor = Vector2(10, 10);
	Vector2 panel_size = Vector2(300, 500);//p_area.x / 4, p_area.y / 3);
	_panel->set_geometry(panel_anchor, panel_size);

	Vector2 name_anchor = Vector2(5, 5);
	Vector2 name_size = Vector2(80, 30);//p_area.x / 4, p_area.y / 3);
	_name_label->set_geometry(name_anchor, name_size);

	Vector2 entry_anchor = Vector2(10 + name_size.x, 0.0f) + name_anchor;
	Vector2 entry_size = Vector2(panel_size.x - name_size.x - 20, name_size.y);//p_area.x / 4, p_area.y / 3);
	_name_entry->set_geometry(entry_anchor, entry_size);
}

bool c_map::handle_keyboard()
{
	return (false);
}

bool c_map::handle_mouse()
{
	if (_calib_button->is_pointed(g_mouse->pos) == true)
		return (false);

	if (control_mouvement() == true)
		return (true);
	if (control_zoom() == true)
		return (true);
	if (_state == map_state::normal && control_normal() == true)
		return (true);
	if (_state == map_state::calibration && control_calibration() == true)
		return (true);
	return (false);
}

void c_map::update()
{
	if (_city_selected != nullptr)
	{
		_city_selected->set_name(_name_entry->entry().text());
	}
}
