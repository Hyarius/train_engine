#include "engine.h"

void c_map::control_city_creation(c_city* city)
{
	if (city == nullptr)
		add_city();
	else
		select_city(city);
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

	g_main_window->actualize_rail_event_tab();
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
			c_city* city = check_city();
			c_rail *rail = check_rail();
			if (rail == nullptr)
				control_city_creation(city);
			else
				control_rail_edition(rail);
		}
		_mile_selected = nullptr;
		return (true);
	}
	else if (g_mouse->get_button(mouse_button::right) == mouse_state::up)
	{
		c_milestone* tmp_milestone = check_milestone();
		c_city* tmp_city = check_city();
		c_rail* tmp_rail = check_rail();

		if (tmp_city != nullptr)
			remove_city(tmp_city);
		else if (tmp_milestone != nullptr)
			remove_milestone(tmp_milestone);
		else if (tmp_rail != nullptr)
			remove_rail(tmp_rail);
	}
	return (false);
}

bool c_map::control_unselect()
{
	if (g_mouse->get_button(mouse_button::left) == mouse_state::up && g_mouse->motion == false)
	{
		if (_rail_selected.size() != 0)
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
