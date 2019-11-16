#include "engine.h"

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

float c_train_engine::calc_next_speed(size_t index)
{
	c_train *train = _train_list[index];
	c_journey *journey = _journey_list[index];
	float to_calc = train->speed() * convert_minute_to_hour(_time_delta) + train->distance();
	float actual_speed;

	actual_speed = train->actual_rail()->speed();
	for (size_t i = train->index() + 1; i < journey->path().size() - 1; i++)
	{
		to_calc -= train->actual_rail()->distance();
		if (to_calc < 0)
			return (actual_speed);

		if (journey->path()[i + 1]->place() != nullptr &&
			journey->wait_entry()[i + 1]->value() != 0)
			return (0.0f);

		c_rail *rail = journey->get_rail(_map, i);

		if (rail->speed() != actual_speed)
			return (rail->speed());
	}
	return (actual_speed);
}

void c_train_engine::move_train(size_t index, float distance)
{
	c_train *train = _train_list[index];

	train->add_distance(distance);
	while (train->actual_rail()->distance() - train->distance() < 0.001f)
	{
		train->move_to_next_rail(_map);
		train->set_waiting_time(0);
		if (train->journey()->path()[train->index()]->place() != nullptr)
		{
			train->set_waiting_time(train->journey()->wait_entry()[train->index()]->value());
			if (train->waiting_time() != 0)
				train->set_state(e_train_state::waiting);
		}
		if (train->actual_rail() == nullptr)
		{
			train->change_speed(_time_delta, 0.0f);
			_arrived_train++;
			_arrived_hour[index] = _time;
			break ;
		}
	}
	_distance[index] += distance;
}
