#include "engine.h"

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

	map = new c_map("ressources/image/map.jpg", map_box);

	map->set_geometry(map_delta, map_size);
	map->active();
}

static void start_calculation(Data data)
{
	c_map *map = (c_map *)(data.content[0]);
	map->start_calculation();
}

void c_main_window::create_command_panel()
{
	int border = command_box->box().border();
	Vector2 button_delta = border * 2;
	Vector2 button_size = Vector2(command_box->box().area().x - border * 4,
		(command_box->box().area().y - border * 4) / 2 - border);

	start_button = new c_button(&start_calculation, map, command_box);
	start_button->text().set_text("Start simulation");

	start_button->set_geometry(button_delta, button_size);
	start_button->active();
}

void c_main_window::create_config_panel()
{

}

void c_main_window::create_travel_panel()
{

}

void c_main_window::create_train_panel()
{

}
