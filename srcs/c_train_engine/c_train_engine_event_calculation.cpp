#include "engine.h"

map <string, int> event_active_map;
map <string, vector<float>> event_active_map_time;
std::default_random_engine generator;

static void add_event_to_train(c_journey *journey, c_train *train, Event *event)
{
	journey->output_text() += "			--- A NEW EVENT ---\n";
	journey->output_text() += "			" + event->name + " - (" + convert_time_to_string(event->time) + ") of event\n";
	//std::normal_distribution<double> distribution(event->time,event->time / 10.0f);
	train->set_state(e_train_state::event);
	event_active_map[event->name]++;
	event_active_map_time[event->name].push_back(event->time);

	train->set_event_waiting_time(event->time);
	//train->change_event_waiting_time(distribution(generator));
	train->set_has_event(true);
}

void c_train_engine::calc_event(size_t index, float time)
{
	c_train* train = _journey_list[index]->train();

	if (train->state() == e_train_state::event)
		return ;

	if (train->state() == e_train_state::waiting && train->place() != nullptr)
	{
		for (auto it = train->place()->event_list().begin(); it != train->place()->event_list().end(); it++)
		{
			if (event_city_bool_map[it->second->name] == true)
			{
				float tmp_value = generate_nbr(0, SEC_PER_YEAR / time);

				if (tmp_value < it->second->nbr)
				{
					add_event_to_train(_journey_list[index], train, it->second);
					return ;
				}
			}
		}
	}
	else if (train->actual_rail() != nullptr)
	{
		for (auto it = train->actual_rail()->event_list().begin(); it != train->actual_rail()->event_list().end(); it++)
		{
			if (event_rail_bool_map[it->second->name] == true)
			{
				float tmp_value = generate_nbr(0, SEC_PER_YEAR / time);

				if (tmp_value < it->second->nbr)
				{
					add_event_to_train(_journey_list[index], train, it->second);
					return ;
				}
			}
		}
	}
}

// 0		900
// 31536000
