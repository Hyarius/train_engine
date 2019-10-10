#include "engine.h"

bool c_map::control_calibration()
{
	if (g_mouse->get_button(mouse_button::left) == mouse_state::up)
	{
		if (g_mouse->motion == false)
		{
			place_landmark(convert_to_map_coord(g_mouse->pos));
			if (_landmark1 != Vector2() && _landmark2 != Vector2())
			{
				_state = map_state::normal;
			}
			return (true);
		}
	}
	return (false);
}

void c_map::control_city_creation()
{
	c_city* result = check_city();
	if (result == nullptr)
		add_city();
	else
		select_city(result);
}

void c_map::control_rail_edition(c_rail *rail)
{
	select_rail(rail);
}

void c_map::control_milestone_creation()
{
	c_city* city = check_city();
	c_milestone* milestone = nullptr;

	if (city != nullptr)
		milestone = city->milestone();
	else
		milestone = check_milestone();

	if (milestone == nullptr)
		milestone = add_milestone(nullptr);

	_mile_selected->add_link(milestone);

	_mile_selected = nullptr;
}


bool c_map::control_normal()
{
	if (g_mouse->get_button(mouse_button::left) == mouse_state::down && _mile_selected == nullptr)
	{
		c_milestone* tmp = check_milestone();

		if (tmp != nullptr)
			_mile_selected = tmp;
	}
	else if (g_mouse->get_button(mouse_button::left) == mouse_state::up)
	{
		if (_mile_selected != nullptr)
			control_milestone_creation();
		else if (g_mouse->motion == false)
		{
			c_rail *rail = check_rail();
			if (rail == nullptr)
				control_city_creation();
			else if (rail != nullptr)
				control_rail_edition(rail);
		}
		_mile_selected = nullptr;
		return (true);
	}
	else if (g_mouse->get_button(mouse_button::right) == mouse_state::up)
	{
		c_milestone* tmp_milestone = check_milestone();
		c_city* tmp_city = check_city();

		if (tmp_city != nullptr)
			remove_city(tmp_city);
		else if (tmp_milestone != nullptr)
			remove_milestone(tmp_milestone);
	}
	return (false);
}

bool c_map::control_mouvement()
{
	if (g_mouse->get_button(mouse_button::left) == mouse_state::down)
	{
		if (_mile_selected != nullptr)
			return (false);
		if (g_mouse->rel_pos != Vector2(0, 0))
		{
			_map_anchor = _map_anchor + g_mouse->rel_pos;
			return (true);
		}
	}
	return (false);
}

bool c_map::control_zoom()
{
	if (g_mouse->wheel != 0)
	{
		float ratio_x;
		float ratio_y;

		ratio_x = (_map->size().x * _zoom) / _map_anchor.x;
		ratio_y = (_map->size().y * _zoom) / _map_anchor.y;

		if (g_mouse->wheel > 0 && _zoom * 1.2 <= 12.0f)
			_zoom *= 1.2f;
		else if (g_mouse->wheel < 0 && _zoom * 0.8f >= 0.5f)
			_zoom *= 0.8f;

		_map_anchor.x = (_map->size().x * _zoom) / ratio_x;
		_map_anchor.y = (_map->size().y * _zoom) / ratio_y;

		return (true);
	}
	return (false);
}

bool c_map::control_unselect()
{
	if (g_mouse->get_button(mouse_button::left) == mouse_state::up && g_mouse->motion == false)
	{
		if (_rail_selected != nullptr)
		{
			c_rail *rail = check_rail();
			select_rail(rail);
			return (true);
		}
		if (_city_selected != nullptr)
		{
			c_city *city = check_city();
			select_city(city);
			return (true);
		}
	}

	return (false);
}
