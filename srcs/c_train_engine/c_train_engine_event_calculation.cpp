#include "engine.h"

map <string, int> event_active_map;
std::default_random_engine generator;

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
					std::normal_distribution<double> distribution(it->second->time,it->second->time / 10.0f);
					train->set_state(e_train_state::event);
					event_active_map[it->second->name]++;
					train->change_event_waiting_time(distribution(generator));
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
					std::normal_distribution<double> distribution(it->second->time,it->second->time / 10.0f);
					train->set_state(e_train_state::event);
					event_active_map[it->second->name]++;
					train->change_event_waiting_time(distribution(generator));
				}
			}
		}
	}
}

// 0		900
// 31536000
