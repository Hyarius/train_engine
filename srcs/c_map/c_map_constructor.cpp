#include "engine.h"

static void active_calibatration(Data p_data)
{
	c_map *map = (c_map *)(p_data.content[0]);

	map->set_state(map_state::calibration);
	map->reset_landmark();
}

void c_map::create_city_panel()
{
	_city_panel = new c_frame(this);

	_city_name_label = new c_text_label("City name :", _city_panel);
	_city_name_label->label().set_style(text_style::underline);
	_city_name_label->active();

	_city_name_entry = new c_text_entry("", _city_panel);
	_city_name_entry->entry().set_align(alignment::centred);
	_city_name_entry->active();

	_city_waiting_label = new c_text_label("Time to wait here (min) :", _city_panel);
	_city_waiting_label->label().set_style(text_style::underline);
	_city_waiting_label->active();

	_city_waiting_entry = new c_value_entry(180.0f, _city_panel);
	_city_waiting_entry->entry().set_precision(0);
	_city_waiting_entry->entry().set_align(alignment::centred);
	_city_waiting_entry->active();
}

void c_map::create_rail_panel()
{
	_rail_panel = new c_frame(this);

	_rail_speed_label = new c_text_label("Rail max speed (km/h):", _rail_panel);
	_rail_speed_label->label().set_style(text_style::underline);
	_rail_speed_label->active();

	_rail_speed_entry = new c_value_entry(180.0f, _rail_panel);
	_rail_speed_entry->entry().set_precision(0);
	_rail_speed_entry->entry().set_align(alignment::centred);
	_rail_speed_entry->active();
}

void c_map::create_calib_button()
{
	_calib_button = new c_button(nullptr, nullptr, this);
	_calib_button->text().set_text("Calibration");
	_calib_button->set_action(&active_calibatration, Data(this));
	_calib_button->active();

	_unit_label = new c_text_label("Km", this);
	_unit_label->box().set_back(Color(150, 150, 150));
	_unit_label->box().set_front(Color(195, 195, 195));
	_unit_label->active();

	_landmark_scale = new c_value_entry(1.0f, this);
	_landmark_scale->entry().set_precision(0);
	_landmark_scale->active();
}

void c_map::create_landmark()
{
	_state = map_state::calibration;
	_rel_distance = -1.0f;
	_landmark1 = Vector2();
	_landmark2 = Vector2();
}

c_map::c_map(string path, c_widget *parent) : c_widget(parent)
{
	_map_path = path;
	_map = new c_image(path);
	_map_anchor = _map->size() / -2;
	_zoom = 1.0f;
	_city_selected = nullptr;
	_mile_selected = nullptr;
	_rail_selected.clear();
	_cities.clear();

	create_city_panel();
	create_rail_panel();

	create_calib_button();

	create_landmark();
}
