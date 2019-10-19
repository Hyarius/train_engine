#include "engine.h"

void c_map::load_milestone(fstream &file)
{
	c_milestone *milestone;
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

			if (tab[0] == "pos")
			{
				tab[1].erase(remove(tab[1].begin(), tab[1].end(), '('), tab[1].end());
				tab[1].erase(remove(tab[1].begin(), tab[1].end(), ')'), tab[1].end());
				sub_tab = strsplit(tab[1], "/");
				float value[2];
				for (int i = 0; i < 2; i++)
					value[i] = atof(sub_tab[i].c_str());
				milestone = new c_milestone(Vector2(value[0], value[1]));

				for (size_t v = 0; v < _cities.size(); v++)
				{
					if (_cities[v]->is_here(milestone->pos()))
					{
						milestone->set_place(_cities[v]);
						_cities[v]->set_milestone(milestone);
					}
				}
			}

		}
		text = get_str(file);
		text.erase(remove(text.begin(), text.end(), '\t'), text.end());
	}

	_milestones.push_back(milestone);
}

void c_map::load_milestones(fstream &file)
{
	string text = "";

	while (file.eof() == false && text != "]" && text != "],")
	{
		text = get_str(file);
		text.erase(remove(text.begin(), text.end(), '\t'), text.end());

		if (text == "{")
			load_milestone(file);
	}
}
