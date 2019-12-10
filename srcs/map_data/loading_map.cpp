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
		cout << "Here 1" << endl;
		text = get_str(file);
			cout << "Here 2" << endl;

		if (text == "")
			break;
				cout << "Here 3" << endl;

		remove_char(text, "\t,\"");
			cout << "Here 4" << endl;

		tab = strsplit(text, ":");
			cout << "Here 5" << endl;

		if (tab[0] == "map_image")
		{
			cout << "Here 5.0" << endl;
			reload_map(tab[1]);
			cout << "Here 5.1" << endl;
		}
		else if (tab[0] == "landmarks")
		{
			cout << "Here 6" << endl;
			tab[1].erase(remove(tab[1].begin(), tab[1].end(), '('), tab[1].end());
			tab[1].erase(remove(tab[1].begin(), tab[1].end(), ')'), tab[1].end());
			tab[1].erase(remove(tab[1].begin(), tab[1].end(), ' '), tab[1].end());
			cout << "Here 7" << endl;
			sub_tab = strsplit(tab[1], "/");
			cout << "Nb sub: " << sub_tab.size() << endl;
			for (size_t i = 0; i < sub_tab.size(); i++)
				cout << "Tab[" << i << "] = [" << sub_tab[i] << "]" << endl;
				cout << "Here 8" << endl;
			float value[4];
			for (int i = 0; i < 4; i++)
			{
				cout << "Here 8.0" << endl;
				cout << "Tab -> " << sub_tab[i] << endl;
				const char *char_value = sub_tab[i].c_str();
				cout << "Here 8.1" << endl;
				value[i] = atof(char_value);
				cout << "Here 8.2" << endl;
			}
				cout << "Here 9" << endl;
			place_landmark(Vector2(value[0], value[1]), 0);
			place_landmark(Vector2(value[2], value[3]), 1);
				cout << "Here 10" << endl;
			_state = e_map_state::normal;
				cout << "Here 11" << endl;
		}
		else if (tab[0] == "landmark_scale")
		{
			cout << "Here 12" << endl;
			_rel_distance = atof(tab[1].c_str());
				cout << "Here 13" << endl;
			_landmark_scale->entry().set_value(_rel_distance);
				cout << "Here 14" << endl;
		}
		else if (tab[0] == "cities")
			load_cities(file);
		else if (tab[0] == "milestones")
			load_milestones(file);
		else if (tab[0] == "rails")
			load_rails(file);
	}
}
