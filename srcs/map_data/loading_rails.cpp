#include "engine.h"

void c_rail::load_event(fstream &file)
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
				event->time = atoi(tab[1].c_str());
			else if (tab[0] == "}" || tab[0] == "},")
				add_event(event);
		}

		text = get_str(file);
		text.erase(remove(text.begin(), text.end(), '\t'), text.end());
	}
}

void c_map::load_rail(fstream &file)
{
	c_rail *rail = nullptr;
	c_milestone *first = nullptr;
	c_milestone *second = nullptr;
	float speed = 180.0f;
	float cantonnal_dist = 2.0f;
	bool dual_ways = true;
	bool even_overtake = false;
	bool odd_overtake = false;
	int i;
	string text = "";
	vector<string> tab;
	vector<string> sub_tab;
	int index_0;
	int index_1;

	while (file.eof() == false && text != "}" && text != "},")
	{
		if (text != "")
		{
			tab = strsplit(text, ":");

			for (size_t i = 0; i < tab.size(); i++)
			{
				tab[i].erase(remove(tab[i].begin(), tab[i].end(), '\"'), tab[i].end());
				tab[i].erase(remove(tab[i].begin(), tab[i].end(), ','), tab[i].end());
			}
			if (tab[0] == "speed")
				speed = atof(tab[1].c_str());
			else if (tab[0] == "event" && rail != nullptr)
				rail->load_event(file);
			else if (tab[0] == "dual ways")
				dual_ways = (tab[1] == "true" ? true : false);
			else if (tab[0] == "even overtake")
				even_overtake = (tab[1] == "true" ? true : false);
			else if (tab[0] == "odd overtake")
				odd_overtake = (tab[1] == "true" ? true : false);
			else if (tab[0] == "cantonal dist")
				cantonnal_dist = atof(tab[1].c_str());
			else if (tab[0] == "id_a")
			{
				index_0 = atoi(tab[1].c_str());
				first = get_milestone(index_0);
			}
			else if (tab[0] == "id_b")
			{
				index_1 = atoi(tab[1].c_str());
				second = get_milestone(index_1);

				if (first != nullptr && second != nullptr)
				{
					pair_milestone key = pair_milestone(first, second);
					pair_milestone inv_key = pair_milestone(second, first);

					if (map_contain<pair_milestone, c_rail *>(_rails, key) == true || map_contain<pair_milestone, c_rail *>(_rails, inv_key) == true)
					{
						cout << "bad rail : " << index_0 << " / " << index_1 << endl;
						rail = nullptr;
					}
					else
					{
						first->add_link(second);
						_rails[key]->set_speed(speed);
						_rails[key]->set_dual_ways(dual_ways);
						_rails[key]->set_way_overtake(e_way_type::even, even_overtake);
						_rails[key]->set_way_overtake(e_way_type::odd, odd_overtake);
						_rails[key]->set_cantonal_dist(cantonnal_dist);
						rail = _rails[key];
					}
				}
			}


		}
		text = get_str(file);
		text.erase(remove(text.begin(), text.end(), '\t'), text.end());
	}
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
