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
			float time_past = convert_hour_to_minute(train->distance() / ((train->speed() + train->old_speed()) / 2));
			_distance[index] -= train->distance();
			train->set_distance(0);
			_time -= time_past;
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

void c_train_engine::draw_train_information(size_t i)
{
	c_train* train = _train_list[i];
	string text;

	train->journey()->output_file() << convert_hour_to_string(_time) << " : ";

	text = normalize_float(train->speed(), 0, '0', 3);
	// text = ftoa(train->speed(), 0);
	// while (text.size() < 3)
	// 	text.insert(text.begin(), '0');

	train->journey()->output_file() << "[" << text << " km/h] ";

	float ratio_dist = (train->distance() * 100.0f) / train->actual_rail()->distance();

	if (train->waiting_time() > 0.0f || train->departure_time() > _time)
		text = " waiting ";
	else
	{
		text = ftoa(_distance[i], 1);
		while (text.size() < 6)
			text.insert(text.begin(), '0');
		text.append(" km");
	}

	train->journey()->output_file() << "[" << text << "] ";
}

void c_train_engine::draw_train_state(size_t i)
{
	c_train* train = _train_list[i];
	string text;

	train->journey()->output_file() << convert_hour_to_string(_time) << " : "
			<< "[" << (train->state() == e_train_state::waiting ? " waiting " : " " + normalize_float(train->speed(), 0, '0', 3) + " km/h") << "] "
			<< "[" << normalize_float(_distance[i], 1, '0', 6) << " km] ";

	for (size_t j = 0; j < train->journey()->path().size() - 1; j++)
	{
		c_rail *rail = train->journey()->get_rail(_map, j);
		size_t t = train->journey()->get_rail(_map, j)->train_list().size();

		if (t == 1)
			text = normalize_string(to_string(rail->train_list()[0]->num()), '0', 2);
		else
			text = (t == 0 ? "  " : "MM");

		train->journey()->output_file() << (j != 0 ? "-" : "") <<  "[" << text << "]";
	}
	train->journey()->output_file() << endl;
}

void c_train_engine::change_mode_to_slow(size_t index)
{

}

void c_train_engine::slow_down_train(size_t index)
{

}

void c_train_engine::speed_up_train(size_t index)
{
	float result = _time_delta;
	c_train *train = _train_list[index];
	float target_speed;

	target_speed = train->actual_rail()->speed();
	if (train->speed() + train->speed_gain(_time_delta) > target_speed)
	{
		result = _time_delta * (target_speed - train->speed()) / train->speed_gain(_time_delta);
		train->accelerate(_time_delta * (target_speed - train->speed()) / train->speed_gain(_time_delta));

	}
	else if (train->speed() + train->speed_gain(_time_delta) < target_speed)
	{
		train->accelerate(_time_delta);
	}
	else
		cout << "We are perfect" << endl;
	return (result);
}

void c_train_engine::iterate()
{
	if (_time >= 60 * 24)
		_time -= 60 * 24;

	_time += _time_delta;

	for (size_t i = 0; i < _train_list.size(); i++)
	{
		c_train* train = _train_list[i];

		if (train->actual_rail() != nullptr)
		{
			if (train->state() != e_train_state::starting)
				draw_train_state(i);


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
		_train_list[i]->set_departure_time(_journey_list[i]->hour_panel()[0]->value());
		_train_list[i]->set_actual_rail(_journey_list[i]->get_rail(_map, _train_list[i]->index()));
		_distance.push_back(0.0f);
		_arrived_hour.push_back(0.0f);
	}

	for (size_t i = 0; i < 15; i++)
		speed_up_train(0);
	// _arrived_train = 0;
	//
	// while (_arrived_train < _journey_list.size())
	// {
	// 	iterate();
	// }
	//
	// for (size_t i = 0; i < _journey_list.size(); i++)
	// {
	// 	string text = "Total distance for train [" + _journey_list[i]->name() + "] = " + ftoa(_distance[i], 3) + " and arrived at : [" + convert_hour_to_string(_arrived_hour[i]) + "]";
	// 	_journey_list[i]->output_file() << text << endl;
	// 	_journey_list[i]->close_output_file();
	// }
}
