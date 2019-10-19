#include "engine.h"

c_map *g_map;

c_main_window::c_main_window()
{
	map = nullptr;

	create_box();

	create_map_panel();
	create_command_panel();
	create_config_panel();
	create_travel_panel();
	create_train_panel();
}

void c_main_window::create_box()
{
	vector<c_frame **> frames = {&map_box, &train_box, &command_box, &config_box, &travel_box};

	Vector2 pos[5];
	Vector2 size[5];

	pos[0] = Vector2(5, 5);
	size[0] = Vector2(0.8f, 0.7f) * g_application->size();
	pos[1] = pos[0] + Vector2(0.0f, size[0].y + 5);
	size[1] = Vector2(size[0].x, g_application->size().y - 5 - pos[1].y);
	pos[2] = pos[0] + Vector2(size[0].x + 5, 0.0f);
	size[2] = Vector2(g_application->size().x - 5 - pos[2].x, 0.1f * g_application->size().y);
	pos[3] = pos[2] + Vector2(0.0f, size[2].y + 5);
	size[3] = Vector2(size[2].x, 0.4f * g_application->size().y);
	pos[4] = pos[3] + Vector2(0.0f, size[3].y + 5);
	size[4] = Vector2(size[2].x, g_application->size().y - 5 - pos[4].y);

	for (int i = 0; i < 5; i++)
	{
		(*(frames[i])) = new c_frame();
		(*(frames[i]))->set_geometry(pos[i], size[i]);
		(*(frames[i]))->active();
	}
}

void c_main_window::create_map_panel()
{
	Vector2 map_delta = map_box->box().border();
	Vector2 map_size = map_box->box().area() - map_delta * 2;

	g_map = new c_map("ressources/image/map_speed.png", map_box);
	map = g_map;

	g_map->load_map("ressources/data/save/map_data.json");

	g_map->set_geometry(map_delta, map_size);
	g_map->active();
}

void c_main_window::create_command_panel()
{
	int border = command_box->box().border();
	Vector2 button_pos = border * 2;
	Vector2 button_size = Vector2(command_box->box().area().x - border * 4,
		(command_box->box().area().y - border * 3) / 2 - border);

	start_button = new c_button(nullptr, nullptr, command_box);
	start_button->text().set_text("Start simulation");
	start_button->set_geometry(button_pos, button_size);
	start_button->active();

	Vector2 hour_pos = button_pos + Vector2(0.0f, button_size.y + border);
	Vector2 hour_size = button_size;

	hour_entry = new c_hour_entry(12.0f, 0.0f, command_box);

	hour_entry->set_geometry(hour_pos, hour_size);
	hour_entry->active();
}

void c_main_window::create_config_panel()
{

}


static void new_path(Data data)
{
	c_map *map = (c_map *)(data.content[0]);
	map->create_new_path();
}

void c_main_window::create_travel_panel()
{
	int border = travel_box->box().border();
	Vector2 pos = border * 2;
	Vector2 size = Vector2((travel_box->box().area().x / 3) - border * 2, 40.0f);

	new_button = new c_button(&new_path, map, travel_box);
	new_button->text().set_text("New trip");
	new_button->set_geometry(pos, size);
	new_button->active();

	pos.x += size.x + border;
	save_button = new c_button(nullptr, nullptr, travel_box);
	save_button->text().set_text("Save trip");
	save_button->set_geometry(pos, size);
	save_button->active();

	pos.x += size.x + border;
	erase_button = new c_button(nullptr, nullptr, travel_box);
	erase_button->text().set_text("Erase trip(s)");
	erase_button->set_geometry(pos, size);
	erase_button->active();
}

void c_main_window::create_train_panel()
{

}
