#include "engine.h"

static void new_path(Data data)
{
	g_map->create_new_path();
}

static void save_journey(Data data)
{
	c_main_window *win = data.acces<c_main_window *>(0);
	saving_journey();
	win->load_travel_checkbox();
}

static void delete_journey(Data data)
{
	c_main_window *win = data.acces<c_main_window *>(0);

	for (size_t i = 0; i < win->travel_name.size(); i++)
	{
		if (win->travel_name[i]->check().state() == true)
		{
			string path = "ressources/data/path/" + win->travel_name[i]->text().text() + ".json";
			remove(path.c_str());
		}
	}

	win->load_travel_checkbox();
}

void c_main_window::load_travel_checkbox()
{
	for (size_t i = 0; i < travel_name.size(); i++)
		delete travel_name[i];

	travel_name.clear();

	vector<string> files = list_files("ressources/data/path", ".json");

	for (size_t i = 0; i < files.size(); i++)
	{
		c_check_box *test = new c_check_box(files[i], false, travel_panel);
		test->set_geometry(Vector2(10, 10 + 40 * i), Vector2(travel_panel->area().x - 20 - scroll_bar->area().x, 35.0f));
		test->active();

		travel_name.push_back(test);
	}
}

void c_main_window::create_travel_panel()
{
	int border = travel_box->box().border();
	Vector2 pos = border * 1;
	Vector2 size = Vector2((travel_box->box().area().x / 3) - border * 2, 40.0f);

	new_button = new c_button(&new_path, nullptr, travel_box);
	new_button->text().set_text("New trip");
	new_button->set_geometry(pos, size);
	new_button->active();

	pos.x += size.x + border;
	save_button = new c_button(&save_journey, this, travel_box);
	save_button->text().set_text("Save trip");
	save_button->set_geometry(pos, size);
	save_button->active();

	pos.x += size.x + border;
	erase_button = new c_button(&delete_journey, this, travel_box);
	erase_button->text().set_text("Erase trip(s)");
	erase_button->set_geometry(pos, size);
	erase_button->active();

	pos = Vector2(0.0f, border + size.y) + (border * 1);
	size = travel_box->box().area() - border * 3 - pos;

	travel_panel = new c_frame(travel_box);
	travel_panel->viewport()->set_active(true);
	travel_panel->set_geometry(pos, size);
	travel_panel->active();

	pos = Vector2(travel_panel->area().x - 20.0f, 0.0f);
	size = Vector2(20.0f, size.y - travel_panel->box().border() * 2);

	scroll_bar = new c_vscroll_bar(travel_panel);
	scroll_bar->set_geometry(pos, size);
	scroll_bar->active();

	load_travel_checkbox();
}
