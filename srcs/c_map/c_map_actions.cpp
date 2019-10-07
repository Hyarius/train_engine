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

	_panel->set_active(!(city == nullptr));
	if (_city_selected != nullptr)
		_name_entry->entry().set_text(_city_selected->name());
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
	vector<c_milestone*>::iterator it;

	it = find(_milestones.begin(), _milestones.end(), to_remove);
	if (it != _milestones.end())
	{
		delete to_remove;
		_milestones.erase(it);
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
