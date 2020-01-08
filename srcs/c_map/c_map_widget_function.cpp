#include "engine.h"

void c_map::set_geometry_event_menu()
{
	Vector2 button_pos;
	Vector2 message_size;
	Vector2 message_pos;
	Vector2 button_size;
	Vector2 button_anchor;
	Vector2 label_size;
	Vector2 label_anchor;
	Vector2 entry_size;
	Vector2 entry_anchor;

	message_size = area() / 2;
	message_pos = anchor() + (area() / 2) / 2;
	_create_event_frame->set_geometry(message_pos, message_size);

	button_size = Vector2(message_size.x / 5, 30.0f);
	button_pos = Vector2(message_size.x / 10, message_size.y - 60);
	_create_valid_button->set_geometry(button_pos, button_size);

	button_size = Vector2(message_size.x / 5, 30.0f);
	button_pos = message_size - Vector2(message_size.x / 10 + button_size.x, 60.0f);
	_create_cancel_button->set_geometry(button_pos, button_size);

	label_anchor = Vector2((message_size.x / 3) / 2, 50.0f);
	label_size = Vector2(message_size.x / 3 - 5, 30.0f);
	entry_anchor = label_anchor + Vector2(label_size.x + 10.0f, 0.0f);

	_create_event_name_label->set_geometry(label_anchor, label_size);
	_create_event_name_entry->set_geometry(entry_anchor, label_size);
	label_anchor.y += (5 + label_size.y);
	entry_anchor.y += (5 + label_size.y);
	_create_event_nbr_label->set_geometry(label_anchor, label_size);
	_create_event_nbr_entry->set_geometry(entry_anchor, label_size);
	label_anchor.y += (5 + label_size.y);
	entry_anchor.y += (5 + label_size.y);
	_create_event_time_label->set_geometry(label_anchor, label_size);
	_create_event_time_entry->set_geometry(entry_anchor, label_size);
	label_anchor.y += (5 + label_size.y);
	entry_anchor.y += (5 + label_size.y);

	message_size = area() / 2;
	message_pos = anchor() + (area() / 2) / 2;
	_delete_event_frame->set_geometry(message_pos, message_size);

	button_size = Vector2(message_size.x / 5, 30.0f);
	button_pos = Vector2(message_size.x / 10, message_size.y - 60);
	_delete_valid_button->set_geometry(button_pos, button_size);

	button_size = Vector2(message_size.x / 5, 30.0f);
	button_pos = message_size - Vector2(message_size.x / 10 + button_size.x, 60.0f);
	_delete_cancel_button->set_geometry(button_pos, button_size);

	label_anchor = Vector2((message_size.x / 3) / 2, 5.0f);
	label_size = Vector2((message_size.x / 3) * 2 - 5, 30.0f);
	_delete_event_label->set_geometry(label_anchor, label_size);

	Vector2 area_anchor = Vector2(0.0f, label_anchor.y + label_size.y) + 5;
	Vector2 area_area = _delete_event_frame->area() - area_anchor - Vector2(5.0f, 5 + (message_size.y - button_pos.y));
	_delete_event_scroll_area->set_geometry(area_anchor, area_area);

	_delete_scroll_bar->set_geometry(Vector2(area_area.x - 20, 0.0f) - _delete_event_scroll_area->border(), Vector2(20.0f, area_area.y));
}

void c_map::set_geometry_city_panel()
{
	Vector2 panel_anchor = Vector2(10, 10);
	Vector2 panel_size = Vector2(area().x / 4, area().y / 2);
	_city_panel->set_geometry(panel_anchor, panel_size);

	Vector2 label_anchor = Vector2(5, 5);
	Vector2 label_size = Vector2(80, 30);//p_area.x / 4, p_area.y / 3);
	_city_name_label->set_geometry(label_anchor, label_size);

	Vector2 entry_anchor = Vector2(10 + label_size.x, 0.0f) + label_anchor;
	Vector2 entry_size = Vector2(panel_size.x - label_size.x - 25, label_size.y);//p_area.x / 4, p_area.y / 3);
	_city_name_entry->set_geometry(entry_anchor, entry_size);

	label_anchor.y += (5 + label_size.y);
	_city_nb_channel_label->set_geometry(label_anchor, label_size);
	entry_anchor.y += (5 + label_size.y);
	_city_nb_channel_entry->set_geometry(entry_anchor, entry_size);
	label_anchor.y += (5 + label_size.y);

	Vector2 button_size = Vector2((panel_size.x - 25) / 2, label_size.y);
	_city_add_event_button->set_geometry(label_anchor, button_size);
	_city_remove_event_button->set_geometry(label_anchor + Vector2(button_size.x + 10, 0.0f), button_size);
	label_anchor.y += (5 + label_size.y);

	panel_size = panel_size - label_anchor - 10;//p_area.x / 4, p_area.y / 3);
	_city_event_panel->set_geometry(label_anchor, panel_size);
	_city_event_scroll_bar->set_geometry(Vector2(panel_size.x - 20, 0.0f) - _city_event_panel->border(), Vector2(20.0f, panel_size.y));
	label_anchor.y += (5 + label_size.y);
	entry_anchor.y += (5 + label_size.y);
	label_size = Vector2((panel_size.x - 40) / 3, label_size.y);
	entry_size = Vector2((panel_size.x - label_size.x - 40) / 2 - 10, label_size.y);
	label_anchor = 5;
	entry_anchor = label_anchor + Vector2(label_size.x + 10, 0.0f);
	Vector2 entry_anchor2 = entry_anchor + Vector2(entry_size.x, 0.0f);
	for (int i = 0; i < _city_event_name_entry.size(); i++)
	{
		_city_event_name_entry[i]->set_geometry(label_anchor, label_size);
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
	Vector2 panel_size = Vector2(area().x / 4, area().y / 1.5f);
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
	label_anchor.y += (5 + label_size.y);

	Vector2 button_size = Vector2((panel_size.x - 25) / 2, label_size.y);
	_rail_add_event_button->set_geometry(label_anchor, button_size);
	_rail_remove_event_button->set_geometry(label_anchor + Vector2(button_size.x + 10, 0.0f), button_size);
	label_anchor.y += (5 + label_size.y);

	panel_size = panel_size - label_anchor - 10;//p_area.x / 4, p_area.y / 3);
	_rail_event_panel->set_geometry(label_anchor, panel_size);
	_rail_event_scroll_bar->set_geometry(Vector2(panel_size.x - 20, 0.0f) - _rail_event_panel->border(), Vector2(20.0f, panel_size.y));
	label_anchor.y += (5 + label_size.y);
	entry_anchor.y += (5 + label_size.y);
	label_size = Vector2((panel_size.x - 40) / 3, label_size.y);
	entry_size = Vector2((panel_size.x - label_size.x - 40) / 2 - 10, label_size.y);
	label_anchor = 5;
	entry_anchor = label_anchor + Vector2(label_size.x + 10, 0.0f);
	Vector2 entry_anchor2 = entry_anchor + Vector2(entry_size.x, 0.0f);
	for (int i = 0; i < _rail_event_name_entry.size(); i++)
	{
		_rail_event_name_entry[i]->set_geometry(label_anchor, label_size);
		_rail_nb_event_entry[i]->set_geometry(entry_anchor, entry_size);
		_rail_event_duration_entry[i]->set_geometry(entry_anchor2, entry_size);

		label_anchor.y += (5 + label_size.y);
		entry_anchor.y += (5 + label_size.y);
		entry_anchor2.y += (5 + label_size.y);
	}
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
	set_geometry_event_menu();
}

bool c_map::handle_keyboard()
{
	if (g_keyboard->get_key(SDL_SCANCODE_ESCAPE) == 1)
	{
		if (create_event_frame()->is_active() == true)
			create_event_frame()->desactivate();
		else if (delete_event_frame()->is_active() == true)
			delete_event_frame()->desactivate();
		else if (_state != e_map_state::normal)
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

	if (create_event_frame()->is_active() == true)
		return (false);
	else if (delete_event_frame()->is_active() == true)
		return (false);

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
		for (size_t i = 0; i < _city_event_name_entry.size(); i++)
		{
			_city_selected->event_list(_city_event_name_entry[i]->text())->nbr = _city_nb_event_entry[i]->value();
			_city_selected->event_list(_city_event_name_entry[i]->text())->time = _city_event_duration_entry[i]->value();
		}
	}
	for (size_t i = 0; i < _rail_selected.size(); i++)
	{
		_rail_selected[i]->set_speed(_rail_speed_entry->entry().value());
		_rail_selected[i]->set_dual_ways(_rail_dual_ways_box->check().state());
		_rail_selected[i]->set_cantonal_dist(_rail_canton_entry->entry().value());
		_rail_selected[i]->set_way_overtake(e_way_type::odd, _rail_odd_overtake_box->check().state());
		_rail_selected[i]->set_way_overtake(e_way_type::even, _rail_even_overtake_box->check().state());
		for (size_t j = 0; j < _rail_event_name_entry.size(); j++)
		{
			_rail_selected[i]->event_list(_rail_event_name_entry[j]->text())->name = _rail_event_name_entry[j]->text();
			_rail_selected[i]->event_list(_rail_event_name_entry[j]->text())->nbr = _rail_nb_event_entry[j]->value();
			_rail_selected[i]->event_list(_rail_event_name_entry[j]->text())->time = _rail_event_duration_entry[j]->value();
		}
	}
	if (_state == e_map_state::travel_definition)
	{

	}

	for (auto it = event_city_bool_map.begin(); it != event_city_bool_map.end(); it++)
		it->second = g_main_window->city_event_checkers[it->first]->state();

	for (auto it = event_rail_bool_map.begin(); it != event_rail_bool_map.end(); it++)
		it->second = g_main_window->rail_event_checkers[it->first]->state();

	for (auto it = g_main_window->base_city_event_nbr.begin(); it != g_main_window->base_city_event_nbr.end(); it++)
		_new_city_event[it->first]->nbr = it->second->value();

	for (auto it = g_main_window->base_city_event_time.begin(); it != g_main_window->base_city_event_time.end(); it++)
		_new_city_event[it->first]->time = it->second->value();

	for (auto it = g_main_window->base_rail_event_nbr.begin(); it != g_main_window->base_rail_event_nbr.end(); it++)
		_new_rail_event[it->first]->nbr = it->second->value();

	for (auto it = g_main_window->base_rail_event_time.begin(); it != g_main_window->base_rail_event_time.end(); it++)
		_new_rail_event[it->first]->time = it->second->value();

}
