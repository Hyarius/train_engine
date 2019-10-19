#include "engine.h"

void save_destination(Data data)
{
	fstream &file = *(data.acces<fstream *>(0));
	c_journey *journey = (data.acces<c_journey *>(1));
	c_milestone *target = *(data.acces<c_milestone **>(2));

	size_t index = g_map->get_milestone_id(target);
	size_t path_index = journey->get_index(target);

	c_hour_entry *hour_entry = journey->hour_panel()[path_index];

	json_add_value(file, 3, "id", to_string(index));

	string hour = "";

	if (hour_entry != nullptr && path_index != journey->path().size() - 1)
		hour = hour_entry->hour().text() + "h" + hour_entry->minute().text();

	json_add_value(file, 3, "departure time", hour);
}

void saving_journey()
{
	if (g_map->journey() == nullptr)
		return ;

	c_journey *journey = g_map->journey();

	c_milestone *start = journey->path()[0];
	c_milestone *end = journey->path().back();
	c_hour_entry *panel = journey->hour_panel()[0];
	if (start->place() == nullptr || end->place() == nullptr)
		return ;

	string name = start->place()->name() + "-" + end->place()->name() + "-" + panel->hour().text() + "h" + panel->minute().text();
	fstream file = open_file("ressources/data/path/" + name + ".json", ios_base::out);

	json_add_line(file, 0, "{");

	json_add_vector<c_milestone *>(file, 1, "destination", journey->path(), &save_destination, Data (2, &file, journey));

	json_add_line(file, 0, "}");

	file.close();
}
