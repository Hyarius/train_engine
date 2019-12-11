#include "engine.h"

static void load_point(fstream &file, c_journey *journey)
{
	size_t index = -1;
	pair_int hour = pair_int(0, 0);
	int waiting = 5;
	string text = "";
	vector<string> tab;
	vector<string> sub_tab;

	text = get_str(file);
	while (file.eof() == false && text != "]" && text != "],")
	{
		tab = strsplit(text, ":");

		for (size_t i = 0; i < tab.size(); i++)
			tab[i].erase(remove(tab[i].begin(), tab[i].end(), '\"'), tab[i].end());

		if (tab[0] == "id")
			index = atoi(tab[1].c_str());
		else if (tab[0] == "},")
			journey->add_point(g_map->get_milestone(index), hour, waiting);
		else if (tab[0] == "Waiting time")
			waiting = atoi(tab[1].c_str());
		else if (tab[0] == "departure time")
		{
			tab[1].erase(remove(tab[1].begin(), tab[1].end(), '('), tab[1].end());
			tab[1].erase(remove(tab[1].begin(), tab[1].end(), ')'), tab[1].end());
			sub_tab = strsplit(tab[1], "h");
			if (sub_tab.size() == 2)
			{
				int value[2];
				for (int i = 0; i < 2; i++)
					value[i] = atoi(sub_tab[i].c_str());
				hour = pair_int(value[0], value[1]);
			}
		}
		text = get_str(file);
		text.erase(remove(text.begin(), text.end(), '\t'), text.end());
	}
}

c_journey *load_journey(string path)
{
	c_journey *result = new c_journey();

	fstream file = open_file(path, ios_base::in);

	if (file.good() == false)
		return (result);

	vector<string> tab;
	string text = "";

	text = get_str(file);
	while (file.eof() == false)
	{
		text.erase(remove(text.begin(), text.end(), '\t'), text.end());
		text.erase(remove(text.begin(), text.end(), '\"'), text.end());
		tab = strsplit(text, ":");

		if (tab[0] == "destination")
			load_point(file, result);
		else if (tab[0] == "train speed")
		{
			cout << "New speed : " << ftoa(atof(tab[1].c_str())) << endl;
			result->train()->set_speed(atof(tab[1].c_str()));
		}
		else if (tab[0] == "train acceleration")
			result->train()->set_acceleration(atof(tab[1].c_str()));
		else if (tab[0] == "train deceleration")
			result->train()->set_deceleration(atof(tab[1].c_str()));
		text = get_str(file);
	}

	return (result);
}
