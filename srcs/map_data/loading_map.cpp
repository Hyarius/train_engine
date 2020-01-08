#include "engine.h"

void c_map::reload_map(string path)
{
	if (_map != nullptr)
		delete _map;

	_map_path = path;
	_map = new c_image(path);
	_map_anchor = _map->size() / -2;
	_zoom = 1.0f;
}

void c_map::load_event(fstream &file, int state)
{
	Event *event;
	string text = "";
	vector<string> tab;

	while (file.eof() == false && text != "]" && text != "],")
	{
		if (text != "")
		{
			tab = strsplit(text, ":");

			for (size_t i = 0; i < tab.size(); i++)
			{
				tab[i].erase(remove(tab[i].begin(), tab[i].end(), '\"'), tab[i].end());
				tab[i].erase(remove(tab[i].begin(), tab[i].end(), ','), tab[i].end());
			}

			if (tab[0] == "{")
				event = new Event();
			else if (tab[0] == "name")
				event->name = tab[1];
			else if (tab[0] == "nbr")
				event->nbr = atoi(tab[1].c_str());
			else if (tab[0] == "time")
				event->time = atof(tab[1].c_str());
			else if (tab[0] == "}" || tab[0] == "},")
			{
				if (state == 0)
					_new_city_event[event->name] = event;
				else if (state == 1)
					_new_rail_event[event->name] = event;
			}
		}

		text = get_str(file);
		text.erase(remove(text.begin(), text.end(), '\t'), text.end());
	}
}

void c_map::load_map(string path)
{
	fstream file = open_file(path, ios_base::in);

	if (file.good() == false)
		return ;

	string text;
	vector<string> tab;
	vector<string> sub_tab;

	while (file.eof() == false)
	{
		text = string(get_str(file));

		if (text.size() == 0)
			break;

		remove_char(text, "\t,\"");

		tab = strsplit(text, ":");

		if (tab[0] == "map_image")
			reload_map(tab[1]);
		else if (tab[0] == "landmarks")
		{
			tab[1].erase(remove(tab[1].begin(), tab[1].end(), '('), tab[1].end());
			tab[1].erase(remove(tab[1].begin(), tab[1].end(), ')'), tab[1].end());
			tab[1].erase(remove(tab[1].begin(), tab[1].end(), ' '), tab[1].end());
			sub_tab = strsplit(tab[1], string("/"));
			float value[4];
			for (int i = 0; i < 4; i++)
			{
				const char *char_value = sub_tab[i].c_str();
				value[i] = atof(char_value);
			}
			place_landmark(Vector2(value[0], value[1]), 0);
			place_landmark(Vector2(value[2], value[3]), 1);
			_state = e_map_state::normal;
		}
		else if (tab[0] == "landmark_scale")
		{
			_rel_distance = atof(tab[1].c_str());
			_landmark_scale->entry().set_value(_rel_distance);
		}
		else if (tab[0] == "cities")
			load_cities(file);
		else if (tab[0] == "city_event")
			load_event(file, 0);
		else if (tab[0] == "rail_event")
			load_event(file, 1);
		else if (tab[0] == "milestones")
			load_milestones(file);
		else if (tab[0] == "rails")
			load_rails(file);
	}
}
