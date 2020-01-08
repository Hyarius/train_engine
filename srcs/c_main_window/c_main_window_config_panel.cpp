#include "engine.h"

map <string, bool> event_city_bool_map;
map <string, bool> event_rail_bool_map;

void c_main_window::actualize_city_event_tab()
{
	int nb = 0;
	Vector2 size;
	Vector2 pos;

	size = Vector2((city_event_tab->area().x - (config_box->border() * 7) - 20) / 5, 35.0f);
	for (auto it = event_city_bool_map.begin(); it != event_city_bool_map.end(); it++)
	{
		if (map_contain(city_event_checkers, it->first) == false)
		{
			c_check_box *new_checker = new c_check_box(it->first, event_city_bool_map[it->first], city_event_tab);
			city_event_checkers[it->first] = new_checker;
			new_checker->activate();
		}
		pos = Vector2((size.x + config_box->border()) * (nb % 5), (size.y + config_box->border()) * (nb / 5)) + 5;
		city_event_checkers[it->first]->set_geometry(pos, size);

		nb++;
	}
}

void c_main_window::actualize_rail_event_tab()
{
	int nb = 0;
	Vector2 size;
	Vector2 pos;

	size = Vector2((rail_event_tab->area().x - (config_box->border() * 7) - 20) / 5, 35.0f);
	for (auto it = event_rail_bool_map.begin(); it != event_rail_bool_map.end(); it++)
	{
		if (map_contain(rail_event_checkers, it->first) == false)
		{
			c_check_box *new_checker = new c_check_box(it->first, event_rail_bool_map[it->first], rail_event_tab);
			rail_event_checkers[it->first] = new_checker;
			new_checker->activate();
		}
		pos = Vector2((size.x + config_box->border()) * (nb % 5), (size.y + config_box->border()) * (nb / 5)) + 5;
		rail_event_checkers[it->first]->set_geometry(pos, size);

		nb++;
	}
}

void c_main_window::create_base_city_event_panel()
{
	int nb = 0;
	Vector2 size;
	Vector2 label_size;
	Vector2 nbr_size;
	Vector2 time_size;
	Vector2 pos;

	size = Vector2((base_city_event_tab->area().x - (config_box->border() * 7) - 20) / 5, 35.0f);
	label_size = Vector2((size.x - 10) / 2, size.y);
	nbr_size = Vector2((label_size.x - 10) / 2, size.y - 8);
	time_size = Vector2((label_size.x - 10) / 2, size.y - 8);
	for (auto it = map->new_city_event().begin(); it != map->new_city_event().end(); it++)
	{
		pos = Vector2((size.x + config_box->border()) * (nb % 5), (size.y + config_box->border()) * (nb / 5)) + 5;
		c_frame *frame = new c_frame(base_city_event_tab);
		base_city_event_frame[it->first] = frame;
		base_city_event_frame[it->first]->set_geometry(pos, size);
		base_city_event_frame[it->first]->activate();

		base_city_event_label[it->first] = new c_text_label(it->second->name, frame);
		base_city_event_label[it->first]->set_geometry(0, label_size);
		base_city_event_label[it->first]->activate();

		base_city_event_nbr[it->first] = new c_value_entry(it->second->nbr, frame);
		base_city_event_nbr[it->first]->set_precision(0);
		base_city_event_nbr[it->first]->set_border(2);
		base_city_event_nbr[it->first]->set_geometry(Vector2(label_size.x + 10, 1.0f), nbr_size);
		base_city_event_nbr[it->first]->activate();

		base_city_event_time[it->first] = new c_value_entry(it->second->time, frame);
		base_city_event_time[it->first]->set_precision(0);
		base_city_event_time[it->first]->set_border(2);
		base_city_event_time[it->first]->set_geometry(Vector2(label_size.x + 13 + nbr_size.x, 1.0f), time_size);
		base_city_event_time[it->first]->activate();

		nb++;
	}
}

void c_main_window::create_base_rail_event_panel()
{
	int nb = 0;
	Vector2 size;
	Vector2 label_size;
	Vector2 nbr_size;
	Vector2 time_size;
	Vector2 pos;

	size = Vector2((base_rail_event_tab->area().x - (config_box->border() * 7) - 20) / 5, 35.0f);
	label_size = Vector2((size.x - 10) / 2, size.y);
	nbr_size = Vector2((label_size.x - 10) / 2, size.y - 8);
	time_size = Vector2((label_size.x - 10) / 2, size.y - 8);
	for (auto it = map->new_rail_event().begin(); it != map->new_rail_event().end(); it++)
	{
		pos = Vector2((size.x + config_box->border()) * (nb % 5), (size.y + config_box->border()) * (nb / 5)) + 5;
		c_frame *frame = new c_frame(base_rail_event_tab);
		base_rail_event_frame[it->first] = frame;
		base_rail_event_frame[it->first]->set_geometry(pos, size);
		base_rail_event_frame[it->first]->activate();

		base_rail_event_label[it->first] = new c_text_label(it->second->name, frame);
		base_rail_event_label[it->first]->set_geometry(0, label_size);
		base_rail_event_label[it->first]->activate();

		base_rail_event_nbr[it->first] = new c_value_entry(it->second->nbr, frame);
		base_rail_event_nbr[it->first]->set_precision(0);
		base_rail_event_nbr[it->first]->set_border(2);
		base_rail_event_nbr[it->first]->set_geometry(Vector2(label_size.x + 10, 1.0f), nbr_size);
		base_rail_event_nbr[it->first]->activate();

		base_rail_event_time[it->first] = new c_value_entry(it->second->time, frame);
		base_rail_event_time[it->first]->set_precision(0);
		base_rail_event_time[it->first]->set_border(2);
		base_rail_event_time[it->first]->set_geometry(Vector2(label_size.x + 13 + nbr_size.x, 1.0f), time_size);
		base_rail_event_time[it->first]->activate();

		nb++;
	}
}

void c_main_window::create_config_panel()
{
	config_tab = new c_tab(config_box);
	config_tab->set_geometry(config_box->border(), config_box->area() - config_box->border() * 2);
	config_tab->activate();

		// City event part
	city_event_tab = config_tab->add_tab("Infrastructure event", 0);
	city_event_tab_scroll_bar = new c_vscroll_bar(city_event_tab);
	city_event_tab_scroll_bar->set_geometry(Vector2(city_event_tab->area().x - 20 - config_tab->border(), 0.0f), Vector2(20.0f, city_event_tab->area().y - config_tab->border() * 2));
	city_event_tab_scroll_bar->activate();

		// Rail event part
	rail_event_tab = config_tab->add_tab("Train event", 1);
	rail_event_tab_scroll_bar = new c_vscroll_bar(rail_event_tab);
	rail_event_tab_scroll_bar->set_geometry(Vector2(rail_event_tab->area().x - 20 - config_tab->border(), 0.0f), Vector2(20.0f, rail_event_tab->area().y - config_tab->border() * 2));
	rail_event_tab_scroll_bar->activate();

		// Base city event part
	base_city_event_tab = config_tab->add_tab("Base city's events", 2);
	base_city_event_tab_scroll_bar = new c_vscroll_bar(base_city_event_tab);
	base_city_event_tab_scroll_bar->set_geometry(Vector2(base_city_event_tab->area().x - 20 - config_tab->border(), 0.0f), Vector2(20.0f, base_city_event_tab->area().y - config_tab->border() * 2));
	base_city_event_tab_scroll_bar->activate();

		// Base rail event part
	base_rail_event_tab = config_tab->add_tab("Base rail's events", 3);
	base_rail_event_tab_scroll_bar = new c_vscroll_bar(base_rail_event_tab);
	base_rail_event_tab_scroll_bar->set_geometry(Vector2(base_rail_event_tab->area().x - 20 - config_tab->border(), 0.0f), Vector2(20.0f, base_rail_event_tab->area().y - config_tab->border() * 2));
	base_rail_event_tab_scroll_bar->activate();

	actualize_city_event_tab();
	actualize_rail_event_tab();
	create_base_city_event_panel();
	create_base_rail_event_panel();
}
