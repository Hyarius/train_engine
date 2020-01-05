#include "engine.h"

static void save_city_event(Data data)
{
	fstream &file = *(data.acces<fstream *>(0));
	c_city *city = *(data.acces<c_city **>(1));
	Event *event = *(data.acces<Event **>(3));
	json_add_value(file, 5, "name", event->name);
	json_add_value(file, 5, "nbr", to_string(event->nbr));
	json_add_value(file, 5, "time", ftoa(event->time, 0));
}

static void save_rail_event(Data data)
{
	fstream &file = *(data.acces<fstream *>(0));
	c_rail *rail = *(data.acces<c_rail **>(1));
	Event *event = *(data.acces<Event **>(3));

	json_add_value(file, 5, "name", event->name);
	json_add_value(file, 5, "nbr", to_string(event->nbr));
	json_add_value(file, 5, "time", ftoa(event->time, 0));
}

void save_city(Data data)
{
	fstream &file = *(data.acces<fstream *>(0));
	c_city *city = *(data.acces<c_city **>(1));

	json_add_value(file, 3, "name", city->name());
	json_add_value(file, 3, "nb channel", to_string(city->nb_channel()));
	json_add_value(file, 3, "pos", city->pos().str());

	json_add_map(file, 3, "event", city->event_list(), save_city_event, data);
}

void save_milestone(Data data)
{
	fstream &file = *(data.acces<fstream *>(0));
	c_milestone *milestone = *(data.acces<c_milestone **>(1));

	json_add_value(file, 3, "pos", milestone->pos().str());
}

void save_rail(Data data)
{
	fstream &file = *(data.acces<fstream *>(0));
	c_map *map = data.acces<c_map *>(1);
	pair_milestone *key = data.acces<pair_milestone *>(2);
	c_rail *rail = *(data.acces<c_rail **>(3));

	json_add_value(file, 3, "speed", ftoa(rail->speed(), 0));
	json_add_value(file, 3, "dual ways", (rail->dual_ways() == true ? "true" : "false"));
	json_add_value(file, 3, "even overtake", (rail->way_overtake(e_way_type::even) == true ? "true" : "false"));
	json_add_value(file, 3, "odd overtake", (rail->way_overtake(e_way_type::odd) == true ? "true" : "false"));
	json_add_value(file, 3, "cantonal dist", ftoa(rail->cantonal_dist(), 3));

	json_add_value(file, 3, "id_a", to_string(g_map->get_milestone_id(key->first)));
	json_add_value(file, 3, "id_b", to_string(g_map->get_milestone_id(key->second)));



	json_add_map(file, 3, "event", rail->event_list(), save_rail_event, data);
}

static void remove_duplicate_rail(map<pair_milestone, c_rail *> &rails)
{
	for (auto it = rails.begin(); it != rails.end();)
	{
		pair_milestone inv_key = pair_milestone(it->first.second, it->first.first);
		if (map_contain<pair_milestone, c_rail *>(rails, inv_key) == true)
		{
			rails.erase(inv_key);
			it = rails.begin();
		}
		else
			it++;
	}
}

void c_map::quit()
{
	fstream file = open_file("ressources/data/save/map_data.json", ios_base::out);

	json_add_line(file, 0, "{");
	json_add_value(file, 1, "map_image", _map_path);
	json_add_value(file, 1, "landmarks", _landmark1.str() + " / " + _landmark2.str());
	json_add_value(file, 1, "landmark_scale", ftoa(_rel_distance, 3));

	json_add_vector<c_city *>(file, 1, "cities", _cities, &save_city, &file);
	json_add_vector<c_milestone *>(file, 1, "milestones", _milestones, &save_milestone, &file);

	remove_duplicate_rail(_rails);

	// for (auto it = _rails.begin(); it != _rails.end(); it++)
	// {
	// 	for (auto it2 = it->second->event_list().begin(); it2 != it->second->event_list().end(); it2++)
	// 	{
	// 		cout << "=================" << endl;
	// 		cout << "Event name: " << it->second->event_list(it2->first)->name << endl;
	// 		cout << "Event prob: " << it->second->event_list(it2->first)->nbr << endl;
	// 		cout << "Event time: " << it->second->event_list(it2->first)->time << endl;
	// 	}
	// }

	json_add_map<pair_milestone, c_rail *>(file, 1, "rails", _rails, &save_rail, Data(2, &file, this));

	json_add_line(file, 0, "}");
}
