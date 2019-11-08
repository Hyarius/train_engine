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
	float actual_speed;

	actual_speed = _train_list[index]->actual_rail()->speed();
	for (size_t i = _train_list[index]->index() + 1; i < _journey_list[index]->path().size() - 1; i++)
	{
		c_rail *rail = _journey_list[index]->get_rail(_map, i);

		if (_journey_list[index]->path()[i + 1]->place() != nullptr &&
			_journey_list[index]->wait_entry()[i + 1]->value() != 0)
				return (0);
		if (rail->speed() != actual_speed)
			return (rail->speed());
	}
	return (actual_speed);
}

void c_train_engine::handle_train_speed(size_t index)
{
	float tmp = calc_distance_left(index);

	// if (_train_list[index]->waiting_time() > 0)
	// 	_train_list[index]->change_waiting_time(-_time_delta);
	if (tmp <= _train_list[index]->slow_down_dist())
		_train_list[index]->decelerate_to_speed(_time_delta, 0);
	else
		_train_list[index]->accelerate_to_speed(_time_delta, _train_list[index]->actual_rail()->speed());
}

void c_train_engine::handle_train_pos(size_t index)
{
	float tmp_dist = _train_list[index]->speed() * _time_delta / 60;

	_train_list[index]->add_distance(tmp_dist);
	if (_train_list[index]->distance() > _train_list[index]->actual_rail()->distance())
	{
		_train_list[index]->set_distance(_train_list[index]->distance() - _train_list[index]->actual_rail()->distance());
		_train_list[index]->set_index(_train_list[index]->index() + 1);
		_train_list[index]->set_actual_rail(_journey_list[index]->get_rail(_map, _train_list[index]->index()));
		if (_journey_list[index]->path()[_train_list[index]->index()]->place() != nullptr)
			_train_list[index]->set_waiting_time(_journey_list[index]->wait_entry()[_train_list[index]->index()]->value());
		if (_train_list[index]->actual_rail() == nullptr)
			_arrived_train++;
	}
	_distance[index] += tmp_dist;
}

void c_train_engine::iterate()
{
	if (_time >= 60 * 24)
		_time -= 60 * 24;

	for (size_t i = 0; i < _train_list.size(); i++)
	{
		if (i != 0)
			cout << " - ";

		if (_train_list[i]->actual_rail() != nullptr)
		{
			handle_train_pos(i);

			cout << "[" << convert_hour_to_string(_time) << "] - Train [" << i << "] : " <<
					_train_list[i]->speed() << " km/h - Dist left : " << calc_distance_left(i) <<
					" / dist to stop : " << _train_list[i]->slow_down_dist() << endl;

			handle_train_speed(i);
		}
	}

	_time += _time_delta;
}

void c_train_engine::run()
{
	if (_time == -1.0f || _time_delta == -1.0f)
		error_exit(1, "Bad engine configuration : Time [" + ftoa(_time, 2) + "] / Delta [" + ftoa(_time_delta, 2) + "]");

	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		_journey_list[i]->calc_distance(_map);
		_train_list[i]->set_departure_time(_journey_list[i]->hour_panel()[0]->value());
		_train_list[i]->set_actual_rail(_journey_list[i]->get_rail(_map, _train_list[i]->index()));
		_distance.push_back(0.0f);
	}
	_arrived_train = 0;

	while (_arrived_train < _journey_list.size())
	{
		iterate();
	}
	for (size_t i = 0; i < _distance.size(); i++)
		cout << "Total distance for train [" << _journey_list[i]->name() << "] = " << _distance[i] << endl;
}
