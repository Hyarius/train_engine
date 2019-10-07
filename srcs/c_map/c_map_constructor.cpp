#include "engine.h"

static void active_calibatration(Data p_data)
{
	c_map *map = (c_map *)(p_data.content[0]);

	map->set_state(map_state::calibration);
	map->reset_landmark();
}

void c_map::create_panel()
{
	_panel = new c_frame(this);

	_name_label = new c_text_label("City name :", _panel);
	_name_label->label().set_style(text_style::underline);
	_name_label->active();

	_name_entry = new c_text_entry("", _panel);
	_name_entry->entry().set_align(alignment::centred);
	_name_entry->active();
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
	_map = new c_image(path);
	_map_anchor = _map->size() / -2;
	_zoom = 1.0f;
	_city_selected = nullptr;
	_mile_selected = nullptr;
	_cities.clear();

	create_panel();

	create_calib_button();

	create_landmark();
}
