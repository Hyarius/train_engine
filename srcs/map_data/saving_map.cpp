#include "engine.h"

void save_city(Data data)
{
	fstream &file = *(data.acces<fstream *>(0));
	c_city *city = *(data.acces<c_city **>(1));

	json_add_value(file, 3, "name", city->name());
	json_add_value(file, 3, "waiting time", to_string(city->waiting_time()));
	json_add_value(file, 3, "pos", city->pos().str());
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
	pair<c_milestone *, c_milestone *> *key = data.acces<pair<c_milestone *, c_milestone *> *>(2);
	c_rail *rail = *(data.acces<c_rail **>(3));

	json_add_value(file, 3, "speed", ftoa(rail->speed(), 0));

	auto it = find(map->milestones().begin(), map->milestones().end(), key->first);
	size_t i = it - map->milestones().begin();
	cout << "i = " << to_string(i) << endl;
	json_add_value(file, 3, "id_a", to_string(i));


	it = find(map->milestones().begin(), map->milestones().end(), key->second);
	i = it - map->milestones().begin();
	json_add_value(file, 3, "id_b", to_string(i));
}

void c_map::quit()
{
	fstream file = open_file("ressources/data/save/map_data.json", ios_base::out);

	json_add_line(file, 0, "", "{");
	json_add_value(file, 1, "map_image", _map_path);
	json_add_value(file, 1, "map_image", _landmark1.str() + "/" + _landmark2.str());
	json_add_value(file, 1, "landmark_scale", ftoa(_rel_distance, 3));

	json_add_vector<c_city *>(file, 1, "cities", _cities, &save_city, &file);
	json_add_vector<c_milestone *>(file, 1, "milestones", _milestones, &save_milestone, &file);

	json_add_map<pair<c_milestone *, c_milestone *>, c_rail *>(file, 1, "rails", _rails, &save_rail, Data(2, &file, this));
	// write_on_file(file, "\t\"rails\":[");
	//
	// auto final_iter = _rails.end();
	// --final_iter;
	//
	// for (auto it = _rails.begin(); it != _rails.end(); it++)
	// {
	// 	write_on_file(file, "\t\t{");
	// 	save_rail(file, it->first, it->second);
	//
	// 	if (it != final_iter)
	// 		write_on_file(file, "\t\t},");
	// 	else
	// 		write_on_file(file, "\t\t}");
	// }
	// write_on_file(file, "\t]");
	write_on_file(file, "}");
}
