#include "engine.h"

static void calc_journeys(Data data)
{
	c_main_window *win = data.acces<c_main_window *>(0);

	for (int i = 0; i < 100; i++)
	{
		for (size_t i = 0; i < win->travel_name.size(); i++)
		{
			if (win->travel_name[i]->check().state() == true)
				win->engine->add_journey(load_journey("ressources/data/path/" + win->travel_name[i]->label().text() + ".json"));
		}

		win->map->calc_distance_ratio();

		win->engine->run();
		cout << "DONE CALCULATION !" << endl;
		win->engine->clean();
	}
}

void c_main_window::create_command_panel()
{
	engine = new c_train_engine();

	engine->set_time(0, 0);
	engine->set_time_delta(60);

	int border = command_box->box().border();
	Vector2 button_pos = border * 1;
	Vector2 button_size = Vector2(command_box->box().area().x - border * 4,
		(command_box->box().area().y - border * 3) / 2 - border);

	start_button = new c_button(&calc_journeys, this, command_box);
	start_button->set_text("Start simulation");
	start_button->set_geometry(button_pos, button_size);
	start_button->activate();

	Vector2 hour_pos = button_pos + Vector2(0.0f, button_size.y + border);
	Vector2 hour_size = button_size;

	hour_entry = new c_hour_entry(12.0f, 0.0f, command_box);

	hour_entry->set_geometry(hour_pos, hour_size);
	hour_entry->activate();
}
