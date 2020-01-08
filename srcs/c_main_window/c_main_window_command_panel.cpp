#include "engine.h"


static string create_output_folder(string folder_path)
{
	mkdir(folder_path.c_str(), 0775);

	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::ostringstream oss;
	oss << std::put_time(&tm, "-%d-%m-%Y %Hh%M-%Ss");
	string str = oss.str();
	string path = folder_path + "/simulation" + str;
	mkdir(path.c_str(), 0775);
	string text_path = path + "/text result";
	string plot_path = path + "/plot result";
	mkdir(text_path.c_str(), 0775);
	mkdir(plot_path.c_str(), 0775);

	return (path);
}

static void calc_journeys(Data data)
{
	fstream result_file;
	int nb_late = 0;
	c_main_window *win = data.acces<c_main_window *>(0);

	if (win->interval_value_entry->value() <= 0)
		return ;

	win->engine->set_time_delta(win->interval_value_entry->value());
	string result_path = create_output_folder("ressources/result");
	result_file = open_file(result_path + "/simulation_info.txt", ios_base::out);
	for (int i = 0; i < win->nb_value_entry->value(); i++)
	{
		for (size_t i = 0; i < win->travel_name.size(); i++)
		{
			if (win->travel_name[i]->check().state() == true)
				win->engine->add_journey(load_journey("ressources/data/path/" + win->travel_name[i]->label().text() + ".json"));
		}

		win->map->calc_distance_ratio();

		win->engine->run(result_path, i, win->graph_result_check->state(), win->text_result_check->state());
		if (win->engine->is_late() == true)
			nb_late++;
		win->engine->clean();
	}
	result_file << "On " << ftoa(win->nb_value_entry->value(), 0) << " trains simulated\n" << "Only " << nb_late << " where actualy late" << endl;
	result_file << "Reason :" << endl;
	for (auto it = event_active_map.begin(); it != event_active_map.end(); it++)
		result_file << it->first << " - " << it->second << " time(s)" << endl;
	result_file.close();
	for (size_t i = 0; i < win->engine->base_time_travel().size(); i++)
		win->engine->base_time_travel()[i] = -1.0f;
}

void c_main_window::create_command_panel()
{
	engine = new c_train_engine();

	engine->set_time(0, 0);

	int border = command_box->box().border();
	Vector2 button_pos = border * 1;
	Vector2 button_size = Vector2(command_box->box().area().x - border * 4,
		(command_box->box().area().y - border * 5) / 4 - border);

	start_button = new c_button(&calc_journeys, this, command_box);
	start_button->set_text("Start simulation");
	start_button->set_geometry(button_pos, button_size);
	start_button->activate();

	Vector2 pos = button_pos + Vector2(0.0f, button_size.y + border);
	Vector2 size = Vector2((button_size.x - border * 2) / 2, button_size.y / 1.5f);
	interval_value_label = new c_text_label("second per interval :", command_box);
	interval_value_label->set_geometry(pos, size);
	interval_value_label->activate();

	interval_value_entry = new c_value_entry(10.0f, command_box);
	interval_value_entry->set_precision(0);
	interval_value_entry->set_geometry(pos + Vector2(size.x + border * 2, 0.0f), size);
	interval_value_entry->activate();

	pos.y += size.y + border;

	nb_value_label = new c_text_label("Nb simulation try :", command_box);
	nb_value_label->set_geometry(pos, size);
	nb_value_label->activate();

	nb_value_entry = new c_value_entry(100.0f, command_box);
	nb_value_entry->set_geometry(pos + Vector2(size.x + border * 2, 0.0f), size);
	nb_value_entry->activate();

	pos.y += size.y + border;

	size = Vector2(button_size.x, button_size.y / 1.5f);
	graph_result_check = new c_check_box("Result as plot", false, command_box);
	graph_result_check->set_geometry(pos, size);
	graph_result_check->activate();

	pos.y += size.y + border;

	text_result_check = new c_check_box("Result as text file", false, command_box);
	text_result_check->set_geometry(pos, size);
	text_result_check->activate();
}
