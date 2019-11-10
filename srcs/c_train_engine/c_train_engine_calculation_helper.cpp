#include "engine.h"

void write_train_in_file(fstream &myfile, float time, size_t num, float dist, c_train *train)
{
	string text;

	text = "[" + convert_hour_to_string(time) + "] - Train ["
			+ to_string(num) + "] : " + ftoa(train->speed(), 6)
			+ " km/h - Left : " + ftoa(dist, 6)
			+ " / To stop : " + ftoa(train->slow_down_dist(), 6)
			+ " / Tic : " + ftoa(train->distance_per_tic(), 6)
			+ " / State : " + (train->state() == e_train_state::normal ? "Normal" :
								(train->state() == e_train_state::first_slow_down ? "First slowing" :
								(train->state() == e_train_state::slow_down ? "Slowing" :
								(train->state() == e_train_state::speed_up ? "Speeding" :
								(train->state() == e_train_state::waiting ? "Waiting" : "Error" )))));
	myfile << text << endl;
}

float c_train_engine::calc_distance_left(size_t index)
{
	size_t start_pos = _train_list[index]->index();
	float tmp;
	float result;

	result = 0;
	for (size_t i = start_pos; i < _journey_list[index]->path().size() - 1; i++)
	{

		c_rail *rail = _journey_list[index]->get_rail(_map, i);
		tmp = 0;
		if (rail != nullptr)
			tmp = rail->distance();

		result += tmp;

		if (_journey_list[index]->path()[i + 1]->place() != nullptr)
		{
			if (_journey_list[index]->wait_entry()[i + 1]->value() != 0)
				break ;
		}
	}
	result -= _train_list[index]->distance();
	return (result);
}
