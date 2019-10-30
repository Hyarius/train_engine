#include "engine.h"

void c_map::load_rail(fstream &file)
{
	c_rail *rail = nullptr;
	c_milestone *first = nullptr;
	c_milestone *second = nullptr;
	float speed = 180.0f;
	int nb_channel = 1;
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

			if (tab[0] == "speed")
				speed = atof(tab[1].c_str());
			if (tab[0] == "nb channel")
				nb_channel = atof(tab[1].c_str());
			else if (tab[0] == "id_a")
			{
				int index = atoi(tab[1].c_str());
				first = get_milestone(index);
			}
			else if (tab[0] == "id_b")
			{
				int index = atoi(tab[1].c_str());
				second = get_milestone(index);
			}
		}
		text = get_str(file);
		text.erase(remove(text.begin(), text.end(), '\t'), text.end());
	}
	if (first == nullptr || second == nullptr)
		return ;

	first->add_link(second);

	pair_milestone key = pair_milestone(first, second);
	_rails[key]->set_speed(speed);
	_rails[key]->set_nb_channel(nb_channel);
}

void c_map::load_rails(fstream &file)
{
	string text = "";

	while (file.eof() == false && text != "]" && text != "],")
	{
		text = get_str(file);
		text.erase(remove(text.begin(), text.end(), '\t'), text.end());

		if (text == "{")
			load_rail(file);
	}
}
