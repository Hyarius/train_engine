#include "engine.h"

void c_map::reset_event_list()
{
	for (size_t i = 0; i < _city_event_name_entry.size(); i++)
	{
		delete _city_event_name_entry[i];
		delete _city_nb_event_entry[i];
		delete _city_event_duration_entry[i];
	}
	_city_nb_event_entry.clear();
	_city_event_duration_entry.clear();
	_city_event_name_entry.clear();
}

void c_map::parse_event_list()
{
	for (auto it = _city_selected->event_list().begin();
		it != _city_selected->event_list().end();
		it++)
	{
		add_event_to_list(it->second);
	}
}

void c_map::open_journey(string path)
{
	if (_journey != nullptr)
		delete _journey;

	_journey = load_journey(path);
}

size_t c_map::get_milestone_id(c_milestone *target)
{
	auto it = find(_milestones.begin(), _milestones.end(), target);
	size_t i = it - _milestones.begin();

	return (i);
}

c_milestone *c_map::get_milestone(size_t index)
{
	if (index >= _milestones.size())
		return (nullptr);

	return (_milestones[index]);
}

void c_map::create_new_path()
{
	_state = e_map_state::travel_definition;
	if (_journey != nullptr)
		delete _journey;

	_journey = new c_journey();
}

void c_map::place_landmark(Vector2 new_pos, int index)
{
	if (index == -1)
	{
		if (_landmark1 == Vector2())
			_landmark1 = new_pos;
		else
		{
			_landmark2 = new_pos;
			calc_distance_ratio();
		}
	}
	else
	{
		if (index == 0)
			_landmark1 = new_pos;
		else
			_landmark2 = new_pos;
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
		reset_event_list();
		parse_event_list();
		_city_name_entry->entry().set_text(_city_selected->name());
		_city_nb_channel_entry->entry().set_value(static_cast<float>(_city_selected->nb_channel()));
	}
}

void c_map::select_rail(c_rail *rail)
{
	if (_rail_selected.size() != 0 && g_keyboard->get_key(SDL_SCANCODE_LCTRL) == 0)
	{
		for (size_t i = 0; i < _rail_selected.size(); i++)
			_rail_selected[i]->set_state(false);
		_rail_selected.clear();
		_rail_dual_ways_box->check().set_state(false);
		_rail_odd_overtake_box->check().set_state(false);
		_rail_even_overtake_box->check().set_state(false);
	}


	_rail_panel->set_active(!(rail == nullptr));
	if (_rail_selected.size() == 0 && rail != nullptr)
	{
		_rail_speed_entry->entry().set_value(rail->speed());
		_rail_dual_ways_box->check().set_state(rail->dual_ways());
		_rail_canton_entry->entry().set_value(rail->cantonal_dist());
		_rail_odd_overtake_box->check().set_state(rail->way_overtake(e_way_type::odd));
		_rail_even_overtake_box->check().set_state(rail->way_overtake(e_way_type::even));
	}

	if (rail != nullptr)
	{
		_rail_selected.push_back(rail);
		rail->set_state(true);
	}

}

c_milestone *c_map::add_milestone(c_city* p_city)
{
	Vector2 pos = convert_to_map_coord(g_mouse->pos);
	c_milestone* new_milestone = new c_milestone(pos, p_city);

	_milestones.push_back(new_milestone);

	if (p_city != nullptr)
		p_city->set_milestone(new_milestone);

	return (new_milestone);
}

c_city *c_map::add_city()
{
	Vector2 pos = convert_to_map_coord(g_mouse->pos);

	c_city *new_city = new c_city(pos);
	_cities.push_back(new_city);

	add_milestone(new_city);

	return (new_city);
}

void c_map::remove_city(c_city* to_remove)
{
	if (_city_selected != nullptr)
		select_city(nullptr);

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
	vector<map<pair_milestone, c_rail *>::iterator> array;
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

void c_map::remove_rail(c_rail *rail)
{
	auto key = find_key<pair_milestone, c_rail *>(_rails, rail);

	if (key != _rails.end()->first)
	{
		key.first->remove_link(key.second);
		_rails.erase(key);
	}
	key = find_key<pair_milestone, c_rail *>(_rails, rail);

	if (key != _rails.end()->first)
	{
		key.first->remove_link(key.second);
		_rails.erase(key);
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
