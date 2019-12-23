#include "engine.h"

void new_path(Data data)
{
	c_main_window *win = data.acces<c_main_window *>(0);

	g_map->create_new_path();
	win->train_box_frame->activate();
}

void save_journey(Data data)
{
	c_main_window *win = data.acces<c_main_window *>(0);
	saving_journey();
	win->load_travel_checkbox();
}

void delete_journey(Data data)
{
	c_main_window *win = data.acces<c_main_window *>(0);

	for (size_t i = 0; i < win->travel_name.size(); i++)
	{
		if (win->travel_name[i]->check().state() == true)
		{
			string path = "ressources/data/path/" + win->travel_name[i]->label().text() + ".json";
			remove(path.c_str());
		}
	}

	win->load_travel_checkbox();
}

void load_journey(Data data)
{
	c_main_window *win = data.acces<c_main_window *>(0);
	c_map *map = win->map;
	vector<string> tmp_paths;

	win->train_box_frame->desactivate();
	map->set_journey(nullptr);
	for (size_t i = 0; i < win->travel_name.size(); i++)
	{
		if (win->travel_name[i]->check().state() == true)
		{
			string text = "ressources/data/path/" + win->travel_name[i]->label().text() + ".json";

			tmp_paths.push_back(text);
		}
	}
	if (tmp_paths.size() == 1)
	{
		win->train_box_frame->activate();
		map->open_journey(tmp_paths[0]);
		map->set_state(e_map_state::travel_definition);
	}
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
		test->activate();

		travel_name.push_back(test);
	}
}

void c_main_window::create_travel_panel()
{
	int border = travel_box->box().border();
	Vector2 pos = border * 1;
	Vector2 size = Vector2((travel_box->box().area().x / 2) - border * 2, 30.0f);

	new_button = new c_button(&new_path, this, travel_box);
	new_button->set_tileset(tileset);
	new_button->box().set_border(2);
	new_button->set_text("New");
	new_button->set_geometry(pos, size);
	new_button->activate();

	save_button = new c_button(&save_journey, this, travel_box);
	save_button->set_tileset(tileset);
	save_button->box().set_border(2);
	save_button->set_text("Save");
	save_button->set_geometry(pos + Vector2(size.x + border, 0.0f), size);
	save_button->activate();

	pos.y += size.y + border;
	load_button = new c_button(&load_journey, this, travel_box);
	load_button->set_tileset(tileset);
	load_button->box().set_border(2);
	load_button->set_text("Load");
	load_button->set_geometry(pos, size);
	load_button->activate();

	erase_button = new c_button(&delete_journey, this, travel_box);
	erase_button->set_tileset(tileset);
	erase_button->box().set_border(2);
	erase_button->set_text("Erase");
	erase_button->set_geometry(pos + Vector2(size.x + border, 0.0f), size);
	erase_button->activate();

	pos = Vector2(0.0f, (border + size.y) * 2) + (border * 1);
	size = travel_box->box().area() - border * 3 - pos;

	travel_panel = new c_frame(travel_box);
	travel_panel->viewport()->set_active(true);
	travel_panel->set_geometry(pos, size);
	travel_panel->activate();

	pos = Vector2(travel_panel->area().x - 20.0f, 0.0f);
	size = Vector2(20.0f, size.y - travel_panel->box().border() * 2);

	scroll_bar = new c_vscroll_bar(travel_panel);
	scroll_bar->set_geometry(pos, size);
	scroll_bar->activate();

	load_travel_checkbox();
}
