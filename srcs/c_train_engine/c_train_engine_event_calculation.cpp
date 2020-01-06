#include "engine.h"

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
					cout << "Event in city, in simulation " << _simulation_index << " at time " << convert_hour_to_string(_time) << endl;
					train->set_state(e_train_state::event);
					train->change_event_waiting_time(it->second->time);
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
					cout << "Event on rail in simulation " << _simulation_index << " at time " << convert_hour_to_string(_time) << endl;
					train->set_state(e_train_state::event);
					train->change_event_waiting_time(it->second->time);
				}
			}
		}
	}
}

// 0		900
// 31536000
