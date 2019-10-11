#include "engine.h"

void c_map::place_landmark(Vector2 new_pos)
{
	if (_landmark1 == Vector2())
		_landmark1 = new_pos;
	else
	{
		_landmark2 = new_pos;
		calc_distance_ratio();
	}
}

void c_map::select_city(c_city *city)
{
	if (_city_selected != nullptr)
		_city_selected->select(false);

	_city_selected = city;
	if (_city_selected != nullptr)
		_city_selected->select(true);

	_city_panel->set_active(!(city == nullptr));
	if (_city_selected != nullptr)
	{
		_city_name_entry->entry().set_text(_city_selected->name());
		_city_waiting_entry->entry().set_value(_city_selected->waiting_time());
	}
}

void c_map::select_rail(c_rail *rail)
{
	if (_rail_selected.size() != 0 && g_keyboard->get_key(SDL_SCANCODE_LCTRL) == 0)
	{
		for (size_t i = 0; i < _rail_selected.size(); i++)
			_rail_selected[i]->set_state(false);
		_rail_selected.clear();
	}


	_rail_panel->set_active(!(rail == nullptr));
	if (_rail_selected.size() == 0 && rail != nullptr)
		_rail_speed_entry->entry().set_value(rail->speed());

	if (rail != nullptr)
	{
		_rail_selected.push_back(rail);
		rail->set_state(true);
	}

}

c_milestone *c_map::add_milestone(c_city* p_city)
{
	Vector2 pos = convert_to_map_coord(g_mouse->pos);
	c_milestone* new_milestone = new c_milestone(this, pos, p_city);

	_milestones.push_back(new_milestone);

	if (p_city != nullptr)
		p_city->set_milestone(new_milestone);

	return (new_milestone);
}

c_city *c_map::add_city()
{
	Vector2 pos = convert_to_map_coord(g_mouse->pos);

	c_city *new_city = new c_city(this, pos);
	_cities.push_back(new_city);

	add_milestone(new_city);

	return (new_city);
}

void c_map::remove_city(c_city* to_remove)
{
	remove_milestone(to_remove->milestone());

	to_remove->set_milestone(nullptr);

	vector<c_city *>::iterator it;

	it = find(_cities.begin(), _cities.end(), to_remove);
	if (it != _cities.end())
	{
		delete to_remove;
		_cities.erase(it);
	}
}

void c_map::remove_milestone(c_milestone* to_remove)
{
	vector<c_milestone*>::iterator it2;
	vector<map<pair<c_milestone *, c_milestone *>, c_rail *>::iterator> array;
	for (auto it = _rails.begin(); it != _rails.end(); it++)
		if (it->first.first == to_remove || it->first.second == to_remove)
			array.push_back(it);

	for (size_t i = 0; i < array.size(); i++)
		_rails.erase(array[i]);

	it2 = find(_milestones.begin(), _milestones.end(), to_remove);
	if (it2 != _milestones.end())
	{
		delete to_remove;
		_milestones.erase(it2);
	}
}

c_city* c_map::check_city()
{
	for (size_t i = 0; i < _cities.size(); i++)
		if (_cities[i]->clicked(g_mouse->pos) == true)
			return (_cities[i]);

	return (nullptr);
}

c_milestone* c_map::check_milestone()
{
	for (size_t i = 0; i < _milestones.size(); i++)
		if (_milestones[i]->clicked(g_mouse->pos) == true)
			return (_milestones[i]);

	return (nullptr);
}

c_rail *c_map::check_rail()
{
	for (auto it = _rails.begin(); it != _rails.end(); ++it)
	{
		if (it->second != nullptr)
			if (it->second->poly()->is_pointed(g_mouse->pos - anchor(), _zoom) == true)
				return (it->second);
	}

	return (nullptr);
}
