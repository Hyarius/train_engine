#include "engine.h"

void c_main_window::create_map_panel()
{
	Vector2 map_delta = 0;//map_box->box().border();
	Vector2 map_size = map_box->box().area() - map_box->box().border() * 2;

	g_map = new c_map("ressources/image/france_map.png", map_box);
	map = g_map;

	g_map->load_map("ressources/data/save/map_data.json");

	g_map->set_geometry(map_delta, map_size);
	g_map->activate();
}
