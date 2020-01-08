#include "engine.h"

c_map *g_map;

c_main_window::c_main_window()
{
	map = nullptr;
	engine = nullptr;

	create_box();
	tileset = new c_tileset("ressources/image/frame_border.png", Vector2(3, 3));
	create_map_panel();
	create_command_panel();
	create_config_panel();
	create_travel_panel();
	create_train_panel();

	actualize_city_event_tab();
	actualize_rail_event_tab();
}

void c_main_window::create_box()
{
	vector<c_frame **> frames = {&map_box, &config_box, &command_box, &train_box, &travel_box};

	Vector2 pos[5];
	Vector2 size[5];

	pos[0] = Vector2(5, 5);
	size[0] = Vector2(0.8f, 0.7f) * g_application->size();
	pos[1] = pos[0] + Vector2(0.0f, size[0].y + 5);
	size[1] = Vector2(size[0].x, g_application->size().y - 5 - pos[1].y);
	pos[2] = pos[0] + Vector2(size[0].x + 5, 0.0f);
	size[2] = Vector2(g_application->size().x - 5 - pos[2].x, 0.2f * g_application->size().y);
	pos[3] = pos[2] + Vector2(0.0f, size[2].y + 5);
	size[3] = Vector2(size[2].x, 0.2f * g_application->size().y);
	pos[4] = pos[3] + Vector2(0.0f, size[3].y + 5);
	size[4] = Vector2(size[2].x, g_application->size().y - 5 - pos[4].y);

	for (int i = 0; i < 5; i++)
	{
		(*(frames[i])) = new c_frame();
		(*(frames[i]))->set_geometry(pos[i], size[i]);
		(*(frames[i]))->activate();
	}
}
