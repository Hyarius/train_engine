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
			train->add_distance(-train->distance());
			_distance[index] -= train->distance();
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
			train->journey()->output_file() << convert_hour_to_string(_time) << " : ";
			string text;

			text = ftoa(train->speed(), 0);
			while (text.size() < 3)
				text.insert(text.begin(), '0');

			train->journey()->output_file() << "[" << text << " km/h] ";

			float ratio_dist = (train->distance() * 100.0f) / train->actual_rail()->distance();

			if (train->waiting_time() > 0.0f || train->departure_time() > _time)
				text = " waiting ";
			else
			{
				text = ftoa(ratio_dist, 3);
				while (text.size() < 7)
					text.insert(text.begin(), '0');
				text.append(" %");
			}

			train->journey()->output_file() << "[" << text << "] ";

			for (size_t j = 0; j < train->journey()->path().size() - 1; j++)
			{
				if (j != 0)
					train->journey()->output_file() << "-";

				if (train->journey()->get_rail(_map, j)->train_list().size() == 1)
				{
					c_train* tmp_train = train->journey()->get_rail(_map, j)->train_list()[0];
					if (_time < tmp_train->departure_time())
						text = "  ";
					else 
						text = to_string(tmp_train->num());
					while (text.size() < 2)
						text.insert(text.begin(), '0');
				}
				else if (train->journey()->get_rail(_map, j)->train_list().size() == 0)
					text = "  ";
				else if (train->journey()->get_rail(_map, j)->train_list().size() > 1)
					text = "MM";

				train->journey()->output_file() << "[" << text << "]";
			}
			train->journey()->output_file() << endl;

			if (train->state() == e_train_state::starting && train->departure_time() <= _time && train->waiting_time() <= 0.0f)
				train->set_state(e_train_state::normal);

			if (train->state() == e_train_state::normal && train->speed() != train->actual_rail()->speed())
				train->set_state(e_train_state::speed_up);
			else if (train->state() == e_train_state::first_slow_down)
				train->set_state(e_train_state::slow_down);
			else if (train->state() == e_train_state::normal && train->slow_down_dist() >= calc_distance_left(i) - train->distance_per_tic())
				train->set_state(e_train_state::first_slow_down);
			else if (train->state() == e_train_state::slow_down && train->speed() + train->speed_lost(_time_delta) <= 5.0 && calc_distance_left(i) >= 0.001f)
				train->set_state(e_train_state::stopping);
			else if (train->speed() == train->actual_rail()->speed())
				train->set_state(e_train_state::normal);

			if (train->speed() != train->old_speed())
				train->set_old_speed(train->speed());

			if (train->state() == e_train_state::speed_up)
			{
				if (train->speed() < train->actual_rail()->speed())
					train->accelerate_to_speed(_time_delta, train->actual_rail()->speed());
				else if (train->speed() > train->actual_rail()->speed())
					train->decelerate_to_speed(_time_delta, train->actual_rail()->speed());
			}
			else if (train->state() == e_train_state::slow_down)
				train->decelerate_to_speed(_time_delta, 5.0f);
			else if (train->state() == e_train_state::stopping)
				train->decelerate_to_speed(_time_delta, 5.0f);

			if (train->state() == e_train_state::waiting)
			{
				train->change_waiting_time(-_time_delta);
				if (train->departure_time() <= _time)
					if (train->waiting_time() <= 0.0f)
					{
						train->set_state(e_train_state::normal);
						if (train->index() != 0)
							train->journey()->output_file() << "             -----    The train start again    -----" << endl;
					}
			}
			else if (train->state() == e_train_state::first_slow_down)
			{
				float first_dist;
				float first_time;
				float second_dist;
				float second_time;

				first_dist = calc_distance_left(i) - train->slow_down_dist();
				first_time = (first_dist / train->speed()) * 60;
				second_dist = train->distance_per_tic() - first_dist;
				second_time = _time_delta - first_time;

				move_train(i, ((train->old_speed() + train->speed()) / 2) * convert_minute_to_hour(first_time));

				train->decelerate_to_speed(second_time, 5.0f);

				move_train(i, ((train->old_speed() + train->speed()) / 2) * convert_minute_to_hour(second_time));
			}
			else
				move_train(i, ((train->old_speed() + train->speed()) / 2) * convert_minute_to_hour(_time_delta));
		}
	}
}

void c_train_engine::run()
{
	if (_time == -1.0f || _time_delta == -1.0f)
		error_exit(1, "Bad engine configuration : Time [" + ftoa(_time, 2) + "] / Delta [" + ftoa(_time_delta, 2) + "]");

	_time = 24 * 60;

	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		if (_time > _journey_list[i]->hour_panel()[0]->value())
			_time = _journey_list[i]->hour_panel()[0]->value();
		_journey_list[i]->calc_distance(_map);
		_journey_list[i]->create_output_file();
		_journey_list[i]->output_file() << "Calculation for the travel [" << _journey_list[i]->name() << "] with the train num [" << _train_list[i]->num() << "]" << endl;
		_journey_list[i]->get_rail(_map, 0)->add_train(_train_list[i]);
		_train_list[i]->set_departure_time(_journey_list[i]->hour_panel()[0]->value());
		_train_list[i]->set_actual_rail(_journey_list[i]->get_rail(_map, _train_list[i]->index()));
		_distance.push_back(0.0f);
		_arrived_hour.push_back(0.0f);
	}
	_arrived_train = 0;

	while (_arrived_train < _journey_list.size())
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
