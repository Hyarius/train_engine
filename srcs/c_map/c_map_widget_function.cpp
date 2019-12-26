#include "engine.h"

void c_map::set_geometry_city_panel()
{
	Vector2 panel_anchor = Vector2(10, 10);
	Vector2 panel_size = Vector2(300, 500);//p_area.x / 4, p_area.y / 3);
	_city_panel->set_geometry(panel_anchor, panel_size);

	Vector2 label_anchor = Vector2(5, 5);
	Vector2 label_size = Vector2(80, 30);//p_area.x / 4, p_area.y / 3);
	_city_name_label->set_geometry(label_anchor, label_size);

	Vector2 entry_anchor = Vector2(10 + label_size.x, 0.0f) + label_anchor;
	Vector2 entry_size = Vector2(panel_size.x - label_size.x - 20, label_size.y);//p_area.x / 4, p_area.y / 3);
	_city_name_entry->set_geometry(entry_anchor, entry_size);

	label_anchor.y += (5 + label_size.y);
	_city_nb_channel_label->set_geometry(label_anchor, label_size);
	entry_anchor.y += (5 + label_size.y);
	_city_nb_channel_entry->set_geometry(entry_anchor, entry_size);
	label_anchor.y += (5 + label_size.y);

	panel_size = panel_size - label_anchor - 10;//p_area.x / 4, p_area.y / 3);
	_city_event_panel->set_geometry(label_anchor, panel_size);
	_event_scroll_bar->set_geometry(Vector2(panel_size.x - 15, 5.0f), Vector2(20.0f, panel_size.y));
	label_anchor.y += (5 + label_size.y);
	entry_anchor.y += (5 + label_size.y);
	label_size = Vector2((panel_size.x - 40) / 3, label_size.y);
	entry_size = Vector2((panel_size.x - label_size.x - 40) / 2 - 10, label_size.y);
	label_anchor = 5;
	entry_anchor = label_anchor + Vector2(label_size.x + 10, 0.0f);
	Vector2 entry_anchor2 = entry_anchor + Vector2(entry_size.x, 0.0f);
	for (int i = 0; i < _city_event_text_label.size(); i++)
	{
		_city_event_text_label[i]->set_geometry(label_anchor, label_size);
		_city_nb_event_entry[i]->set_geometry(entry_anchor, entry_size);
		_city_event_duration_entry[i]->set_geometry(entry_anchor2, entry_size);

		label_anchor.y += (5 + label_size.y);
		entry_anchor.y += (5 + label_size.y);
		entry_anchor2.y += (5 + label_size.y);
	}
}

void c_map::set_geometry_rail_panel()
{
	Vector2 panel_anchor = Vector2(10, 10);
	Vector2 panel_size = Vector2(300, 500);//p_area.x / 4, p_area.y / 3);
	_rail_panel->set_geometry(panel_anchor, panel_size);

	Vector2 label_anchor = Vector2(5, 5);
	Vector2 label_size = Vector2(180, 30);//p_area.x / 4, p_area.y / 3);
	_rail_speed_label->set_geometry(label_anchor, label_size);

	Vector2 entry_anchor = Vector2(10 + label_size.x, 0.0f) + label_anchor;
	Vector2 entry_size = Vector2(panel_size.x - label_size.x - 20, label_size.y);//p_area.x / 4, p_area.y / 3);
	_rail_speed_entry->set_geometry(entry_anchor, entry_size);

	label_anchor.y += (5 + label_size.y);
	_rail_canton_label->set_geometry(label_anchor, label_size);

	entry_anchor.y += (5 + label_size.y);
	_rail_canton_entry->set_geometry(entry_anchor, entry_size);

	label_anchor.y += (5 + label_size.y);
	Vector2 check_size = Vector2(panel_size.x - 20, label_size.y);//p_area.x / 4, p_area.y / 3);
	_rail_dual_ways_box->set_geometry(label_anchor, check_size);

	label_anchor.y += (5 + label_size.y);
	_rail_even_overtake_box->set_geometry(label_anchor, check_size);

	label_anchor.y += (5 + label_size.y);
	_rail_odd_overtake_box->set_geometry(label_anchor, check_size);
}

void c_map::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	Vector2 button_size = Vector2(150, 30);
	Vector2 button_pos = this->area() - 5 - button_size;
	_calib_button->set_geometry(button_pos, button_size);

	button_pos.y -= 35;
	button_size.x = 100;
	_landmark_scale->set_geometry(button_pos, button_size);

	button_pos.x += 105;
	button_size.x = 45;
	_unit_label->set_geometry(button_pos, button_size);

	_zoom = 1.0f;
	while (_map->size().x * _zoom < p_area.x)
		_zoom += 0.2f;

	_map_anchor = (_map->size() * _zoom) / -2;

	set_geometry_city_panel();
	set_geometry_rail_panel();
}

bool c_map::handle_keyboard()
{
	if (g_keyboard->get_key(SDL_SCANCODE_ESCAPE) == 1)
	{
		if (_state != e_map_state::normal)
		{
			_state = e_map_state::normal;
			if (_journey != nullptr)
			{
				delete _journey;
				_journey = nullptr;
			}
		}
		else if (_city_selected != nullptr)
			select_city(nullptr);
		else if (_rail_selected.size() != 0)
		{
			for (size_t i = 0; i < _rail_selected.size(); i++)
				_rail_selected[i]->set_state(false);
			_rail_selected.clear();
		}
		else
			g_application->quit();
		g_keyboard->reset_key(SDL_SCANCODE_ESCAPE);
	}
	return (false);
}

bool c_map::handle_mouse()
{
	_rail_even_overtake_box->set_active(_rail_dual_ways_box->check().state());
	_rail_odd_overtake_box->set_active(_rail_dual_ways_box->check().state());

	if (is_pointed(g_mouse->pos) == false)
		return (false);

	if (_calib_button->is_pointed(g_mouse->pos) == true)
		return (false);

	if ((_city_panel->is_active() == true && _city_panel->is_pointed(g_mouse->pos) == true) ||
		(_rail_panel->is_active() == true && _rail_panel->is_pointed(g_mouse->pos) == true))
		return (false);

	if (control_mouvement() == true)
		return (true);
	if (control_zoom() == true)
		return (true);

	if (control_unselect() == true)
		return (true);

	if (_state == e_map_state::normal && control_normal() == true)
		return (true);
	if (_state == e_map_state::calibration && control_calibration() == true)
		return (true);
	if (_state == e_map_state::travel_definition && control_travel_definition() == true)
		return (true);

	return (false);
}

void c_map::update()
{
	_rel_distance = _landmark_scale->entry().value();
	if (_city_selected != nullptr)
	{
		_city_selected->set_name(_city_name_entry->entry().text());
		_city_selected->set_nb_channel(static_cast<int>(_city_nb_channel_entry->entry().value()));
	}
	for (size_t i = 0; i < _rail_selected.size(); i++)
	{
		_rail_selected[i]->set_speed(_rail_speed_entry->entry().value());
		_rail_selected[i]->set_dual_ways(_rail_dual_ways_box->check().state());
		_rail_selected[i]->set_cantonal_dist(_rail_canton_entry->entry().value());
		_rail_selected[i]->set_way_overtake(e_way_type::odd, _rail_odd_overtake_box->check().state());
		_rail_selected[i]->set_way_overtake(e_way_type::even, _rail_even_overtake_box->check().state());
	}
	if (_state == e_map_state::travel_definition)
	{

	}
}
