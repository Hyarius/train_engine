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

float c_train_engine::calc_slow_down_time(size_t index)
{
	c_train *train = _train_list[index];

	if (train->speed() + train->speed_lost(_time_delta) < 0)
		return (_time_delta * (5.0f - train->speed() / train->speed_lost(_time_delta)));
	else
		return (_time_delta);
}

float c_train_engine::calc_speed_up_time(size_t index)
{
	c_train *train = _train_list[index];
	float rail_speed;

	rail_speed = train->actual_rail()->speed();
	if (train->speed() + train->speed_gain(_time_delta) > rail_speed)
	{
		return (_time_delta * ((rail_speed - train->speed()) / train->speed_gain(_time_delta)));
	}
	else
		return (_time_delta);
}

float c_train_engine::stop_train(size_t index)
{
	return (_time_delta);
}

float c_train_engine::calc_run_time(size_t index)
{
	c_train* train = _train_list[index];
	float dist;

	dist = calc_distance_left(index);
	if (dist <= train->slow_down_dist() + train->distance_per_tic())
	{
		if (train->distance_per_tic() == 0)
			return (0.0f);
		float tmp = train->slow_down_dist() + train->distance_per_tic() - dist;
		float ratio = tmp / train->distance_per_tic();
		return (_time_delta * ratio);
	}
	return (_time_delta);
}

float c_train_engine::calc_wait_time(size_t index)
{
	c_train* train = _train_list[index];
	float delta;

	delta = _time_delta;
	if (train->waiting_time() < delta)
		delta = train->waiting_time();

	train->change_waiting_time(-delta);

	return (delta);
}

void c_train_engine::iterate()
{
	if (_time >= 60 * 24)
		_time -= 60 * 24;

	float time_left = 0;
	float delta;
	float dist;
	//_time += _time_delta;

	for (size_t i = 0; i < _train_list.size(); i++)
	{
		c_train* train = _train_list[i];

		if (train->actual_rail() != nullptr)
		{
			draw_train_state(i);

			while (time_left < _time_delta)
			{
				if (train->state() == e_train_state::waiting && train->waiting_time() <= 0.0f)
					train->set_state(e_train_state::starting);
				if (train->state() == e_train_state::starting && train->departure_time() <= _time)
					train->set_state(e_train_state::speed_up);
				if (train->state() == e_train_state::speed_up && train->speed() == train->actual_rail()->speed())
					train->set_state(e_train_state::normal);

				if (train->state() == e_train_state::speed_up)
				{
					cout << "Here in " << train->state_str() << endl;
					delta = calc_speed_up_time(i);
					dist = train->accelerate(delta);
				}
				else if (train->state() == e_train_state::waiting)
				{
					cout << "Here in " << train->state_str() << endl;
					delta = calc_wait_time(i);
					dist = 0;
				}
				else if (train->state() == e_train_state::speed_down)
				{
					cout << "Here in " << train->state_str() << endl;
					delta = calc_slow_down_time(i);
					dist = train->decelerate(delta);
				}
				else
				{
					cout << "Here in " << train->state_str() << endl;
					delta = calc_run_time(i);
					dist = train->run(delta);
				}

				if (train->state() != e_train_state::waiting)
				{
					cout << "Delta = " << delta << endl;
					move_train(i, dist);
				}

				time_left += delta;
				_time += delta;
			}
		}

	}
}

void c_train_engine::run()
{
	if (_time == -1.0f || _time_delta == -1.0f)
		error_exit(1, "Bad engine configuration : Time [" + ftoa(_time, 2) + "] / Delta [" + ftoa(_time_delta, 2) + "]");
	if (_journey_list.size() == 0)
		return ;

	_time = 24 * 60;

	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		if (_time > _journey_list[i]->hour_panel()[0]->value())
			_time = _journey_list[i]->hour_panel()[0]->value();
		_journey_list[i]->calc_distance(_map);
		_journey_list[i]->create_output_file();
		_journey_list[i]->output_file() << "Calculation for the travel [" << _journey_list[i]->name() << "] with the train num [" << _train_list[i]->num() << "]" << endl;

		_journey_list[i]->output_file() << convert_hour_to_string(_time) << " : ";
		_journey_list[i]->output_file() << "[" << "   STATE  " << "]";
		_journey_list[i]->output_file() << " - [" << "  SPEED " << "]";
		_journey_list[i]->output_file() << " - [" << " dist tot " << "]";
		_journey_list[i]->output_file() << " - [" << " dist left" << "]";
		_journey_list[i]->output_file() << " - [" << " dist stop" << "]";
		_journey_list[i]->output_file() << " - [" << " dist tick" << "]";
		_journey_list[i]->output_file() << endl;

		_train_list[i]->set_departure_time(_journey_list[i]->hour_panel()[0]->value());
		_train_list[i]->set_actual_rail(_journey_list[i]->get_rail(_map, _train_list[i]->index()));
		_train_list[i]->actual_rail()->add_train(_train_list[i]);
		_distance.push_back(0.0f);
		_arrived_hour.push_back(0.0f);
	}

	_arrived_train = 0;

	while (_arrived_train < _journey_list.size() && _time < 60.0f)
	{
		iterate();
	}

	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		string text = "Total distance for train [" + _journey_list[i]->name() + "] = " + ftoa(_distance[i], 3) + " and arrived at : [" + convert_hour_to_string(_arrived_hour[i]) + "]";
		_journey_list[i]->output_file() << text << endl;
		_journey_list[i]->close_output_file();
	}
}
