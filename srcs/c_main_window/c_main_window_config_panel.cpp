#include "engine.h"


map <string, bool> event_city_bool_map;
map <string, bool> event_rail_bool_map;

void c_main_window::create_city_event_tab()
{

}

void c_main_window::create_rail_event_tab()
{

}

void c_main_window::create_config_panel()
{
	config_tab = new c_tab(config_box);
	config_tab->set_geometry(config_box->border(), config_box->area() - config_box->border() * 2);
	config_tab->activate();

	city_event_tab = config_tab->add_tab("Infrastructure event");

	city_event_tab_scroll_bar = new c_vscroll_bar(city_event_tab);
	city_event_tab_scroll_bar->set_geometry(Vector2(city_event_tab->area().x - 20 - config_tab->border(), 0.0f), Vector2(20.0f, city_event_tab->area().y - config_tab->border() * 2));
	city_event_tab_scroll_bar->activate();

	rail_event_tab = config_tab->add_tab("Train event");

	rail_event_tab_scroll_bar = new c_vscroll_bar(rail_event_tab);
	rail_event_tab_scroll_bar->set_geometry(Vector2(rail_event_tab->area().x - 20 - config_tab->border(), 0.0f), Vector2(20.0f, rail_event_tab->area().y - config_tab->border() * 2));
	rail_event_tab_scroll_bar->activate();
}
