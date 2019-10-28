#include "engine.h"

void c_map::load_cities(fstream &file)
{
	string text = "";

	while (file.eof() == false && text != "]" && text != "],")
	{
		text = get_str(file);
		text.erase(remove(text.begin(), text.end(), '\t'), text.end());

		if (text == "{")
			load_city(file);
	}
}

void c_map::load_city(fstream &file)
{
	c_city *city = new c_city();
	int i;
	string text = "";
	vector<string> tab;
	vector<string> sub_tab;

	while (file.eof() == false && text != "}" && text != "},")
	{
		if (text != "")
		{
			tab = strsplit(text, ":");

			for (size_t i = 0; i < tab.size(); i++)
				tab[i].erase(remove(tab[i].begin(), tab[i].end(), '\"'), tab[i].end());

			if (tab[0] == "name")
			{
				tab[1].erase(remove(tab[1].begin(), tab[1].end(), ','), tab[1].end());
				city->set_name(tab[1]);
			}
			else if (tab[0] == "pos")
			{
				tab[1].erase(remove(tab[1].begin(), tab[1].end(), '('), tab[1].end());
				tab[1].erase(remove(tab[1].begin(), tab[1].end(), ')'), tab[1].end());
				sub_tab = strsplit(tab[1], "/");
				float value[2];
				for (int i = 0; i < 2; i++)
					value[i] = atof(sub_tab[i].c_str());
				city->set_pos(Vector2(value[0], value[1]));
			}
		}
		text = get_str(file);
		text.erase(remove(text.begin(), text.end(), '\t'), text.end());
	}

	_cities.push_back(city);
}
