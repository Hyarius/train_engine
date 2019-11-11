#include "engine.h"

fstream myfile;

void write_train_in_file(fstream &myfile, float time, size_t num, float dist, c_train *train);

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
		myfile << "Changing rail : new dist -> " << ftoa(train->distance()) << endl;
		myfile << "Train wait phase : " << to_string(train->waiting_time()) << endl;
		if (train->actual_rail() == nullptr)
		{
			train->change_speed(_time_delta, 0.0f);
			_arrived_train++;
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
		c_train *train = _train_list[i];

		if (i != 0)
			cout << " - ";

		if (_train_list[i]->actual_rail() != nullptr )
		{

			write_train_in_file(myfile, _time, i, calc_distance_left(i), _train_list[i]);

			if (train->state() == e_train_state::normal && train->speed() < train->actual_rail()->speed())
				train->set_state(e_train_state::speed_up);
			else if (train->state() == e_train_state::first_slow_down)
				train->set_state(e_train_state::slow_down);
			else if (train->state() == e_train_state::normal && train->slow_down_dist() >= calc_distance_left(i) - train->distance_per_tic())
				train->set_state(e_train_state::first_slow_down);
			else if (train->state() == e_train_state::slow_down && train->speed() + train->speed_lost(_time_delta) <= 5.0 && calc_distance_left(i) >= 0.001f)
				train->set_state(e_train_state::stopping);
			else if (train->speed() == train->actual_rail()->speed())
				train->set_state(e_train_state::normal);

			float old_speed = train->speed();

			if (train->state() == e_train_state::speed_up)
				train->accelerate_to_speed(_time_delta, train->actual_rail()->speed());
			else if (train->state() == e_train_state::slow_down)
				train->decelerate_to_speed(_time_delta, 5.0f);
			else if (train->state() == e_train_state::stopping)
				train->decelerate_to_speed(_time_delta, 5.0f);

			if (train->state() == e_train_state::waiting)
			{
				train->change_waiting_time(-_time_delta);
				if (train->waiting_time() <= 0.0f)
					train->set_state(e_train_state::normal);
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

				move_train(i, ((old_speed + train->speed()) / 2) * convert_minute_to_hour(first_time));

				train->decelerate_to_speed(second_time, 5.0f);

				move_train(i, ((old_speed + train->speed()) / 2) * convert_minute_to_hour(second_time));
			}
			else
				move_train(i, ((old_speed + train->speed()) / 2) * convert_minute_to_hour(_time_delta));
			myfile << "	-----" << endl;
		}
	}
}

void c_train_engine::run()
{
	if (_time == -1.0f || _time_delta == -1.0f)
		error_exit(1, "Bad engine configuration : Time [" + ftoa(_time, 2) + "] / Delta [" + ftoa(_time_delta, 2) + "]");

	myfile.open("ressources/data/log.txt", ios_base::out);

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
	{
		write_train_in_file(myfile, _time, i, calc_distance_left(i), _train_list[i]);
		string text = "Total distance for train [" + _journey_list[i]->name() + "] = " + ftoa(_distance[i], 3) + " and arrived at : [" + convert_hour_to_string(_time) + "]";
		myfile << text << endl;
		cout << text << endl;
	}


	myfile.close();
}
