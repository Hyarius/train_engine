#include "engine.h"

void activate_calibatration(Data p_data)
{
	c_map *map = (c_map *)(p_data.content[0]);

	map->set_state(e_map_state::calibration);
	map->reset_landmark();
}

void start_event_creation(Data p_data)
{
	c_map *map = (c_map *)(p_data.content[0]);

	if (map->create_event_frame()->is_active() == true)
		return ;
	else if (map->delete_event_frame()->is_active() == true)
		return ;

	map->create_event_frame()->activate();
}

void cancel_creation(Data p_data)
{
	c_map *map = (c_map *)(p_data.content[0]);

	map->create_event_frame()->desactivate();
}

void valide_creation(Data p_data)
{
	c_map *map = (c_map *)(p_data.content[0]);

	if (map->rail_selected().size() == 0)
		map->add_event_to_cities(map->get_event());
	else
		map->add_event_to_rail(map->get_event());

	map->create_event_frame()->desactivate();
}

void start_event_removal(Data p_data)
{
	c_map *map = (c_map *)(p_data.content[0]);

	if (map->create_event_frame()->is_active() == true)
		return ;
	else if (map->delete_event_frame()->is_active() == true)
		return ;

	map->delete_event_frame()->activate();
}

void cancel_removal(Data p_data)
{
	c_map *map = (c_map *)(p_data.content[0]);

	map->delete_event_frame()->desactivate();
}

void valide_removal(Data p_data)
{
	c_map *map = (c_map *)(p_data.content[0]);

	vector<string> to_delete;
	for (size_t i = 0; i < map->delete_event_selector().size(); i++)
		if (map->delete_event_selector(i)->state() == true)
			to_delete.insert(to_delete.end(), string(map->delete_event_selector(i)->text()));

	for (size_t i = 0; i < to_delete.size(); i++)
	{
		if (map->rail_selected().size() == 0)
			map->city_selected()->event_list().erase(to_delete[i]);
		else
		{
			for (size_t j = 0; j < map->rail_selected().size(); j++)
				map->rail_selected(j)->event_list().erase(to_delete[i]);
		}
	}

	map->reset_event_list();
	if (map->city_selected() == nullptr)
		map->parse_rail_event_list();
	else
		map->parse_city_event_list();


	map->delete_event_frame()->desactivate();
}

void c_map::add_city_event_to_list(Event *event)
{
	c_text_label *tmp_text_label;
	tmp_text_label = new c_text_label(event->name, _city_event_panel);
	tmp_text_label->activate();
	tmp_text_label->set_style(text_style::underline);

	c_value_entry *tmp_nbr_entry;
	tmp_nbr_entry = new c_value_entry(event->nbr, _city_event_panel);
	tmp_nbr_entry->activate();
	tmp_nbr_entry->set_precision(0);
	tmp_nbr_entry->set_align(alignment::centred);

	c_value_entry *tmp_time_entry;
	tmp_time_entry = new c_value_entry(event->time, _city_event_panel);
	tmp_time_entry->activate();
	tmp_time_entry->set_precision(0);
	tmp_time_entry->set_align(alignment::centred);

	Vector2 label_size = Vector2((_city_event_panel->area().x - 40) / 3, 30.0f);
	Vector2 entry_size = label_size;
	Vector2 label_anchor = Vector2(0.0f, _city_nb_event_entry.size() * (label_size.y + 5)) + 5;
	Vector2 entry_anchor = label_anchor + Vector2(label_size.x + 5, 0.0f);
	Vector2 entry2_anchor = entry_anchor + Vector2(entry_size.x + 5, 0.0f);

	tmp_text_label->set_geometry(label_anchor, label_size);
	tmp_nbr_entry->set_geometry(entry_anchor, entry_size);
	tmp_time_entry->set_geometry(entry2_anchor, entry_size);

	_city_nb_event_entry.push_back(tmp_nbr_entry);
	_city_event_duration_entry.push_back(tmp_time_entry);
	_city_event_name_entry.push_back(tmp_text_label);
}

void c_map::add_rail_event_to_list(Event *event)
{
	c_text_label *tmp_text_label;
	tmp_text_label = new c_text_label(event->name, _rail_event_panel);
	tmp_text_label->activate();
	tmp_text_label->set_style(text_style::underline);

	c_value_entry *tmp_nbr_entry;
	tmp_nbr_entry = new c_value_entry(event->nbr, _rail_event_panel);
	tmp_nbr_entry->activate();
	tmp_nbr_entry->set_precision(0);
	tmp_nbr_entry->set_align(alignment::centred);

	c_value_entry *tmp_time_entry;
	tmp_time_entry = new c_value_entry(event->time, _rail_event_panel);
	tmp_time_entry->activate();
	tmp_time_entry->set_precision(0);
	tmp_time_entry->set_align(alignment::centred);

	Vector2 label_size = Vector2((_rail_event_panel->area().x - 40) / 3, 30.0f);
	Vector2 entry_size = label_size;
	Vector2 label_anchor = Vector2(0.0f, _rail_nb_event_entry.size() * (label_size.y + 5)) + 5;
	Vector2 entry_anchor = label_anchor + Vector2(label_size.x + 5, 0.0f);
	Vector2 entry2_anchor = entry_anchor + Vector2(entry_size.x + 5, 0.0f);

	tmp_text_label->set_geometry(label_anchor, label_size);
	tmp_nbr_entry->set_geometry(entry_anchor, entry_size);
	tmp_time_entry->set_geometry(entry2_anchor, entry_size);

	_rail_nb_event_entry.push_back(tmp_nbr_entry);
	_rail_event_duration_entry.push_back(tmp_time_entry);
	_rail_event_name_entry.push_back(tmp_text_label);
}

void c_map::add_event_to_list_delete(Event *event)
{
	c_check_box *tmp_check_box;
	tmp_check_box = new c_check_box(event->name, false, _delete_event_scroll_area);
	tmp_check_box->activate();
	tmp_check_box->set_style(text_style::underline);

	Vector2 area = Vector2((_delete_event_scroll_area->area().x - 40) / 3, 30.0f);
	int pos_y = _delete_event_selector.size() / 3;
	int pos_x = (_delete_event_selector.size() - (pos_y * 3)) % 3;
	Vector2 pos = Vector2(pos_x * (area.x + 5), pos_y * (area.y + 5)) + 5;
	tmp_check_box->set_geometry(pos, area);
	_delete_event_selector.push_back(tmp_check_box);
}

void c_map::add_event_to_cities(Event *event)
{
	_city_selected->add_event(event);

	if (_city_selected == nullptr)
		add_rail_event_to_list(event);
	else
		add_city_event_to_list(event);
	add_event_to_list_delete(event);
}

void c_map::add_event_to_rail(Event *event)
{
	for (size_t i = 0; i < rail_selected().size(); i++)
		rail_selected(i)->add_event(event);

		if (_city_selected == nullptr)
			add_rail_event_to_list(event);
		else
			add_city_event_to_list(event);
	add_event_to_list_delete(event);
}

Event *c_map::get_event()
{
	Event *tmp;

	tmp = new Event(_create_event_name_entry->text(), _create_event_nbr_entry->value(), _create_event_time_entry->value());

	return (tmp);
}

void c_map::create_event_menu_panel()
{
	_create_event_frame = new c_frame(this);

	_create_valid_button = new c_button(valide_creation, this, _create_event_frame);
	_create_valid_button->set_text("Create");
	_create_valid_button->activate();

	_create_cancel_button = new c_button(cancel_creation, this, _create_event_frame);
	_create_cancel_button->set_text("Cancel");
	_create_cancel_button->activate();

	_create_event_name_label = new c_text_label("New event name :", _create_event_frame);
	_create_event_name_label->set_align(alignment::right);
	_create_event_name_label->set_back(Color(120, 120, 120));
	_create_event_name_label->set_front(Color(160, 160, 160));
	_create_event_name_label->activate();

	_create_event_nbr_label = new c_text_label("New event number per year :", _create_event_frame);
	_create_event_nbr_label->set_align(alignment::right);
	_create_event_nbr_label->set_back(Color(120, 120, 120));
	_create_event_nbr_label->set_front(Color(160, 160, 160));
	_create_event_nbr_label->activate();

	_create_event_time_label = new c_text_label("New event average time duration :", _create_event_frame);
	_create_event_time_label->set_align(alignment::right);
	_create_event_time_label->set_back(Color(120, 120, 120));
	_create_event_time_label->set_front(Color(160, 160, 160));
	_create_event_time_label->activate();

	_create_event_name_entry = new c_text_entry("Default", _create_event_frame);
	_create_event_name_entry->set_back(Color(120, 120, 120));
	_create_event_name_entry->set_front(Color(160, 160, 160));
	_create_event_name_entry->activate();

	_create_event_nbr_entry = new c_value_entry(0.0f, _create_event_frame);
	_create_event_nbr_entry->set_back(Color(120, 120, 120));
	_create_event_nbr_entry->set_front(Color(160, 160, 160));
	_create_event_nbr_entry->activate();

	_create_event_time_entry = new c_value_entry(0.0f, _create_event_frame);
	_create_event_time_entry->set_back(Color(120, 120, 120));
	_create_event_time_entry->set_front(Color(160, 160, 160));
	_create_event_time_entry->activate();

	_delete_event_frame = new c_frame(this);

	_delete_valid_button = new c_button(valide_removal, this, _delete_event_frame);
	_delete_valid_button->set_text("Confirm");
	_delete_valid_button->activate();

	_delete_cancel_button = new c_button(cancel_removal, this, _delete_event_frame);
	_delete_cancel_button->set_text("Cancel");
	_delete_cancel_button->activate();

	_delete_event_label = new c_text_label("Select event(s) to delete", _delete_event_frame);
	_delete_event_label->set_align(alignment::centred);
	_delete_event_label->set_back(Color(120, 120, 120));
	_delete_event_label->set_front(Color(160, 160, 160));
	_delete_event_label->activate();

	_delete_event_scroll_area = new c_frame(_delete_event_frame);
	_delete_event_scroll_area->activate();

	_delete_scroll_bar = new c_vscroll_bar(_delete_event_scroll_area);
	_delete_scroll_bar->activate();
}

void c_map::create_city_panel()
{
	_city_panel = new c_frame(this);

	_city_name_label = new c_text_label("City name :", _city_panel);
	_city_name_label->set_style(text_style::underline);
	_city_name_label->activate();

	_city_name_entry = new c_text_entry("", _city_panel);
	_city_name_entry->set_align(alignment::centred);
	_city_name_entry->activate();

	_city_nb_channel_label = new c_text_label("Nb channel :", _city_panel);
	_city_nb_channel_label->set_style(text_style::underline);
	_city_nb_channel_label->activate();

	_city_nb_channel_entry = new c_value_entry(2.0f, _city_panel);
	_city_nb_channel_entry->set_align(alignment::centred);
	_city_nb_channel_entry->activate();

	_city_event_panel = new c_frame(_city_panel);
	_city_event_panel->activate();

	_city_event_scroll_bar = new c_vscroll_bar(_city_event_panel);
	_city_event_scroll_bar->activate();

	_city_add_event_button = new c_button(start_event_creation, this, _city_panel);
	_city_add_event_button->set_text("Add event");
	_city_add_event_button->activate();

	_city_remove_event_button = new c_button(start_event_removal, this, _city_panel);
	_city_remove_event_button->set_text("Remove event");
	_city_remove_event_button->activate();


}

void c_map::create_rail_panel()
{
	_rail_panel = new c_frame(this);

	_rail_speed_label = new c_text_label("Rail max speed (km/h):", _rail_panel);
	_rail_speed_label->set_style(text_style::underline);
	_rail_speed_label->activate();

	_rail_speed_entry = new c_value_entry(180.0f, _rail_panel);
	_rail_speed_entry->set_precision(0);
	_rail_speed_entry->set_align(alignment::centred);
	_rail_speed_entry->activate();

	_rail_canton_label = new c_text_label("Cantonal dist (km):", _rail_panel);
	_rail_canton_label->set_style(text_style::underline);
	_rail_canton_label->activate();

	_rail_canton_entry = new c_value_entry(2.0f, _rail_panel);
	_rail_canton_entry->set_precision(3);
	_rail_canton_entry->set_align(alignment::centred);
	_rail_canton_entry->activate();

	_rail_dual_ways_box = new c_check_box("Dual ways :", true, _rail_panel);
	_rail_dual_ways_box->set_style(text_style::normal);
	_rail_dual_ways_box->activate();

	_rail_even_overtake_box = new c_check_box("Even overtake way :", false, _rail_panel);
	_rail_even_overtake_box->set_style(text_style::normal);

	_rail_odd_overtake_box = new c_check_box("Odd overtake way :", false, _rail_panel);
	_rail_odd_overtake_box->set_style(text_style::normal);

	_rail_event_panel = new c_frame(_rail_panel);
	_rail_event_panel->activate();

	_rail_event_scroll_bar = new c_vscroll_bar(_rail_event_panel);
	_rail_event_scroll_bar->activate();

	_rail_add_event_button = new c_button(start_event_creation, this, _rail_panel);
	_rail_add_event_button->set_text("Add event");
	_rail_add_event_button->activate();

	_rail_remove_event_button = new c_button(start_event_removal, this, _rail_panel);
	_rail_remove_event_button->set_text("Remove event");
	_rail_remove_event_button->activate();
}

void c_map::create_calib_button()
{
	_calib_button = new c_button(nullptr, nullptr, this);
	_calib_button->set_text("Calibration");
	_calib_button->set_action(&activate_calibatration, Data(this));
	_calib_button->activate();

	_unit_label = new c_text_label("Km", this);
	_unit_label->box().set_back(Color(150, 150, 150));
	_unit_label->box().set_front(Color(195, 195, 195));
	_unit_label->activate();

	_landmark_scale = new c_value_entry(_rel_distance, this);
	_landmark_scale->set_precision(0);
	_landmark_scale->activate();
}

void c_map::create_landmark()
{
	_state = e_map_state::calibration;
	_rel_distance = -1.0f;
	_landmark1 = Vector2();
	_landmark2 = Vector2();
}

c_map::c_map(string path, c_widget *parent) : c_widget(parent)
{
	_map = nullptr;
	_point_image = new c_tileset("ressources/image/point_texture.png", Vector2(3, 1));

	_journey = nullptr;
	_city_selected = nullptr;
	_mile_selected = nullptr;
	_rail_selected.clear();
	_cities.clear();

	create_city_panel();
	create_rail_panel();

	create_event_menu_panel();

	create_landmark();
	create_calib_button();

	reload_map(path);
}
