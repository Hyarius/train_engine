#include "engine.h"

bool c_map::control_click()
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
		{
			c_milestone* tmp = nullptr;
			c_city* tmp_city = check_city();

			if (tmp_city == nullptr)
			{
				tmp = check_milestone();
			}
			else
			{
				tmp = tmp_city->milestone();
			}

			if (tmp == nullptr)
			{
				tmp = add_milestone(nullptr);
			}

			_mile_selected->add_link(tmp);
			_mile_selected = nullptr;

			return (true);
		}
		else if (g_mouse->motion == false)
		{
			if (check_milestone() == nullptr)
			{
				c_city* result = check_city();
				if (_selected == nullptr)
				{
					if (result == nullptr)
						add_city();
					else
						select_city(result);
				}
				else
					select_city(nullptr);

				_mile_selected = nullptr;
				return (true);
			}

		}
		_mile_selected = nullptr;
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

bool c_map::handle_mouse()
{
	if (control_click() == true)
		return (true);
	if (control_mouvement() == true)
		return (true);
	if (control_zoom() == true)
		return (true);
	return (false);
}
