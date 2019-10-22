#include "engine.h"

static void new_path(Data data)
{
	g_map->create_new_path();
}

static void save_journey(Data data)
{
	saving_journey();
}

void c_main_window::create_travel_panel()
{
	int border = travel_box->box().border();
	Vector2 pos = border * 2;
	Vector2 size = Vector2((travel_box->box().area().x / 3) - border * 2, 40.0f);

	new_button = new c_button(&new_path, nullptr, travel_box);
	new_button->text().set_text("New trip");
	new_button->set_geometry(pos, size);
	new_button->active();

	pos.x += size.x + border;
	save_button = new c_button(&save_journey, nullptr, travel_box);
	save_button->text().set_text("Save trip");
	save_button->set_geometry(pos, size);
	save_button->active();

	pos.x += size.x + border;
	erase_button = new c_button(nullptr, nullptr, travel_box);
	erase_button->text().set_text("Erase trip(s)");
	erase_button->set_geometry(pos, size);
	erase_button->active();

	vector<string> files = list_files("ressources/data/path", ".json");

	for (size_t i = 0; i < files.size(); i++)
	{
		cout << "File : [" << files[i] << "]" << endl;
	}

	pos = Vector2(0.0f, border + size.y) + (border * 2);
	size = travel_box->box().area() - border * 2 - pos;

	travel_panel = new c_frame(travel_box);
	travel_panel->set_geometry(pos, size);
	travel_panel->active();

	pos = Vector2(travel_panel->area().x - 20.0f, 0.0f);
	size = Vector2(20.0f, size.y);

	scroll_bar = new c_vscroll_bar(travel_panel);
	scroll_bar->set_geometry(pos, size);
	scroll_bar->active();

	c_button *test = new c_button(nullptr, nullptr, travel_panel);
	test->set_geometry(Vector2(50, 50), Vector2(150, 50));
	test->active();
}
