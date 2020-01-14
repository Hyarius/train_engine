#include "engine.h"

c_map *g_map;

c_main_window::c_main_window()
{
	map = nullptr;
	engine = nullptr;

cout << "Here 0" << endl;
	create_box();
	cout << "Here 1" << endl;
	tileset = new c_tileset("ressources/image/frame_border.png", Vector2(3, 3));
	cout << "Here 2" << endl;
	create_map_panel();
	cout << "Here 3" << endl;
	create_command_panel();
	cout << "Here 4" << endl;
	create_config_panel();
	cout << "Here 5" << endl;
	create_travel_panel();
	cout << "Here 6" << endl;
	create_train_panel();
	cout << "Here 7" << endl;
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
