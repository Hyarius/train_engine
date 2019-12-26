#include "engine.h"



float c_train_engine::calc_distance_left(size_t index)
{
	size_t start_pos = _journey_list[index]->train()->index();
	float tmp;
	float result;

	result = 0;
	for (size_t i = start_pos; i < _journey_list[index]->path().size() - 1; i++)
	{
		c_rail *rail = _journey_list[index]->get_rail(i);
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
	result -= _journey_list[index]->train()->distance();
	return (result);
}

float c_train_engine::calc_next_speed(size_t index)
{
	c_train *train = _journey_list[index]->train();
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

		c_rail *rail = journey->get_rail(i);

		if (rail->speed() != actual_speed)
			return (rail->speed());
	}
	return (actual_speed);
}

void c_train_engine::move_train(size_t index, float distance)
{
	c_train *train = _journey_list[index]->train();

	if (train->actual_rail() == nullptr)
		return ;
	train->add_distance(distance);
	while (train->actual_rail()->distance() - train->distance() < 0.001f)
	{
		train->move_to_next_rail();
		train->set_waiting_time(0);
		if (train->journey()->path(train->index())->place() != nullptr)
		{
			train->set_waiting_time(train->journey()->wait_entry()[train->index()]->value());
			if (train->waiting_time() != 0)
			{
				train->set_place(train->journey()->path(train->index())->place());
				train->place()->add_train_waiting();
				train->set_state(e_train_state::waiting);
			}
		}
		if (train->actual_rail() == nullptr)
		{
			train->change_speed(_time_delta, 0.0f);
			_arrived_train++;
			_arrived_hour[index] = _time_travel[index];
			break ;
		}
	}
	_distance[index] += distance;
}

float c_train_engine::calc_decelerate_time(size_t index, float time_left, float target_speed)
{
	float result;

	c_train *train = _journey_list[index]->train();

	if (target_speed > train->max_speed())
		target_speed = train->max_speed();

	if (train->speed() + train->speed_lost(time_left) < target_speed)
	{
		float ratio = (target_speed - train->speed()) / train->speed_lost(time_left);
		result = time_left * ratio;
	}
	else if (train->distance() + train->distance_per_tic() > train->actual_rail()->distance())
	{
		float dist_to_run = train->actual_rail()->distance() - train->distance();
		float ratio = dist_to_run / train->distance_per_tic();

		result = time_left * ratio;
	}
	else
		result = time_left;

	if (result == 0)
	{
		if (target_speed == MIN_SPEED)
			train->set_state(e_train_state::stopping);
		else
			train->set_state(e_train_state::normal);
	}

	return (result);
}

float c_train_engine::calc_slowing_time(size_t index, float time_left, float target_speed)
{
	float result;

	c_train *train = _journey_list[index]->train();


	if (target_speed > train->max_speed())
		target_speed = train->max_speed();

	if (train->speed() + train->speed_lost(time_left) < target_speed)
	{
		float ratio = (target_speed - train->speed()) / train->speed_lost(time_left);
		result = time_left * ratio;
	}
	else
		result = time_left;

	if (result == 0)
		train->set_state(e_train_state::normal);

	return (result);
}

float c_train_engine::calc_accelerate_time(size_t index, float time_left, float target_speed)
{
	float result;

	c_train *train = _journey_list[index]->train();


	if (target_speed > train->max_speed())
		target_speed = train->max_speed();

	if (train->speed() + train->speed_gain(time_left) > target_speed)
	{
		float ratio = (target_speed - train->speed()) / train->speed_gain(time_left);
		result = time_left * ratio;
		if (result == 0)
			train->set_state(e_train_state::normal);
	}
	else if (train->distance() + train->distance_per_tic() > train->actual_rail()->distance())
	{
		float dist_to_run = train->actual_rail()->distance() - train->distance();
		float ratio = dist_to_run / train->distance_per_tic();

		result = time_left * ratio;
	}
	else
		result = time_left;

	return (result);
}

float c_train_engine::calc_run_time(size_t index, float time_left)
{
	float result;

	c_train *train = _journey_list[index]->train();
	if (train->slow_down_dist() >= calc_distance_left(index) - train->distance_per_tic())
	{
		float dist_to_run = calc_distance_left(index) - train->slow_down_dist();
		float ratio = dist_to_run / train->distance_per_tic();

		train->set_state(e_train_state::speed_down);
		result = time_left * ratio;
	}
	else if (train->distance() + train->distance_per_tic() > train->actual_rail()->distance())
	{
		float dist_to_run = train->actual_rail()->distance() - train->distance();
		float ratio = dist_to_run / train->distance_per_tic();

		result = time_left * ratio;
	}
	else
		result = time_left;

	return (result);
}

float c_train_engine::calc_waiting_time(size_t index, float time_left)
{
	float result;

	c_train *train = _journey_list[index]->train();

	if (time_left <= train->waiting_time())
		result = time_left;
	else
		result = train->waiting_time();

	// if (train->place() != nullptr)
	// 	cout << train->place() << endl;

	return (result);
}
