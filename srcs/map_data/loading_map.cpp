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

void c_map::load_data(string path)
{
	/*fstream file = open_file(path, ios_base::in);

	string text;
	vector<string> tab;
	vector<string> sub_tab;

	while (file.eof() == false)
	{
		text = get_str(file);

		text.erase(std::remove(text.begin(), text.end(), '\t'), text.end());

		tab = strsplit(text, ":");

		for (size_t i = 0; i < tab.size(); i++)
			tab[i].erase(std::remove(tab[i].begin(), tab[i].end(), '\"'), tab[i].end());

		if (tab[0] == "map_image")
			reload_map(tab[1]);
		else if (tab[0] == "landmarks")
		{
			sub_tab = strsplit(tab[1], "/");
			place_landmark(Vector2(atof(sub_tab[0]), atof(sub_tab[1])), 0);
			place_landmark(Vector2(atof(sub_tab[2]), atof(sub_tab[3])), 1);
		}
		else if (tab[0] == "landmark_scale")
			_rel_distance = atof(tab[1]);

	}*/
}
