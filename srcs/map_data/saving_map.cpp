#include "engine.h"

void c_map::save_city(fstream &file, c_city *city)
{
	write_on_file(file, "\t\t\t\"name\":\"" + city->name() + "\",");
	write_on_file(file, "\t\t\t\"waiting time\":\"" + to_string(city->waiting_time()) + "\",");
	write_on_file(file, "\t\t\t\"pos\":\"" + city->pos().str() + "\"");
}

void c_map::save_milestone(fstream &file, c_milestone *milestone)
{
	write_on_file(file, "\t\t\t\"pos\":\"" + milestone->pos().str() + "\",");

	string text = "\t\t\t\"link_to\":\"";

	vector<c_milestone *> tmp = milestone->links_to();

	for (size_t i = 0; i < milestone->links_to().size(); i++)
	{
		if (i != 0)
			text.append("/");
		auto it = find(_milestones.begin(), _milestones.end(), milestone->links_to()[i]);

		text.append(to_string(it - _milestones.begin()));

	}
	text.append("\"");

	write_on_file(file, text);
}

void c_map::save_rail(fstream &file, pair<c_milestone *, c_milestone *> key, c_rail *rail)
{
	write_on_file(file, "\t\t\t\"speed\":\"" + ftoa(rail->speed(), 0) + "\",");

	auto it = find(_milestones.begin(), _milestones.end(), key.first);
	size_t i = it - _milestones.begin();
	write_on_file(file, "\t\t\t\"id_a\":\"" + to_string(i) + "\",");


	it = find(_milestones.begin(), _milestones.end(), key.second);
	i = it - _milestones.begin();
	write_on_file(file, "\t\t\t\"id_b\":\"" + to_string(i) + "\"");
}

void c_map::quit()
{
	fstream file = open_file("ressources/data/save/map_data.json", ios_base::out);

	write_on_file(file, "{");
	write_on_file(file, "\t\"map_image\":\"" + _map_path + "\",");

	string text = "\t\"landmarks\":\"" + _landmark1.str() + "/" + _landmark2.str() + "\",";
	write_on_file(file, text);

	text = "\t\"landmark_scale\":\"" + ftoa(_rel_distance, 3) + "\",";
	write_on_file(file, text);

	write_on_file(file, "\t\"cities\":[");
	for (size_t i = 0; i < _cities.size(); i++)
	{
		write_on_file(file, "\t\t{");
		save_city(file, _cities[i]);
		if (i != _cities.size() - 1)
			write_on_file(file, "\t\t},");
		else
			write_on_file(file, "\t\t}");
	}
	write_on_file(file, "\t],");

	write_on_file(file, "\t\"milestone\":[");
	for (size_t i = 0; i < _milestones.size(); i++)
	{
		write_on_file(file, "\t\t{");
		save_milestone(file, _milestones[i]);
		if (i != _milestones.size() - 1)
			write_on_file(file, "\t\t},");
		else
			write_on_file(file, "\t\t}");
	}
	write_on_file(file, "\t],");

	write_on_file(file, "\t\"rails\":[");

	auto final_iter = _rails.end();
	--final_iter;

	for (auto it = _rails.begin(); it != _rails.end(); it++)
	{
		write_on_file(file, "\t\t{");
		save_rail(file, it->first, it->second);

		if (it != final_iter)
			write_on_file(file, "\t\t},");
		else
			write_on_file(file, "\t\t}");
	}
	write_on_file(file, "\t]");
	write_on_file(file, "}");
}
