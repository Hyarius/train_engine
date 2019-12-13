#include "engine.h"

float max_dist;

bool c_train_engine::can_overtake(size_t index)
{
	c_train* train = _journey_list[index]->train();
	e_way_type type = train->get_way_type();

	//cout << "Here" << endl;

	if (train->actual_rail()->way_overtake(type) == true)
	{
		cout << "True" << endl;
		return (true);
	}
	//cout << "False" << endl;
	return (false);
}

bool c_train_engine::should_slow(size_t train_index)
{
	c_train* train = _journey_list[train_index]->train();
	e_way_type type = train->get_way_type();

	vector<c_train *> train_list;

	for (size_t index = train->index(); index < train->journey()->path().size() -1; index++)
	{
		c_rail *rail = train->get_rail(index);
		if (rail->dual_ways() == false && rail->ways(0).type() != type)
			break;

		for (size_t i = 0; i < rail->train_list(type).size(); i++)
		{
			c_train *tmp = rail->train_list(type)[i];
			if (tmp != train)
			{
				if (tmp->place() == nullptr || (tmp->place()->nb_channel() <= tmp->place()->train_waiting()))
					train_list.push_back(tmp);
			}
		}
	}

	for (size_t i = 0; i < train_list.size(); i++)
	{
		float dist = _distance[train_list[i]->num()] - _distance[train->num()];
		if (dist > 0 && dist <= train->actual_rail()->cantonal_dist())
			return (!(can_overtake(train_index)));
	}

	return (false);
}

void c_train_engine::iterate()
{
	while (_time > 24 * 60)
		_time -= 24 * 60;

	float time_left = 0;
	float delta;
	float dist;

	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		c_train* train = _journey_list[i]->train();

		if (_time_travel[i] < _time && train->actual_rail() != nullptr)
		{
			time_left = _time_delta;

			while (time_left > 0.0001f && train->actual_rail() != nullptr)
			{
				c_rail *rail = train->actual_rail();
				_plot->add_point(_time + (_time_delta - time_left), _distance[i], i);
				train->calc_distance_per_tic(time_left);
				draw_train_state(i);
				if (train->state() == e_train_state::slowing)
					train->set_state(e_train_state::normal);
				if (train->state() == e_train_state::waiting && train->waiting_time() <= 0.0f)
					train->start();
				if (train->state() == e_train_state::starting && train->departure_time() <= _time)
					train->set_state(e_train_state::speed_up);
				if (train->speed() < rail->speed() && train->speed() < train->max_speed() && train->state() == e_train_state::normal)
					train->set_state(e_train_state::speed_up);
				if (train->speed() > rail->speed())
					train->set_state(e_train_state::speed_down);
				if (should_slow(i) == true)
					train->set_state(e_train_state::slowing);
				if (calc_distance_left(i) <= 0.005f)
					train->set_state(e_train_state::stopping);

				float old_speed = train->speed();

				if (train->state() == e_train_state::speed_up)
				{
					delta = calc_accelerate_time(i, time_left, rail->speed());
					train->accelerate(delta);
				}
				else if (train->state() == e_train_state::speed_down)
				{
					if (train->slow_down_dist() >= calc_distance_left(i) - train->distance_per_tic())
						delta = calc_decelerate_time(i, time_left, MIN_SPEED);
					else
						delta = calc_decelerate_time(i, time_left, rail->speed());
					train->decelerate(delta);
				}
				else if (train->state() == e_train_state::slowing)
				{
					if (train->speed() <= MIN_SPEED)
						delta = time_left;
					else
					{
						delta = calc_slowing_time(i, time_left, MIN_SPEED);
						train->decelerate(delta);
					}
				}
				else if (train->state() == e_train_state::waiting)
				{
					delta = calc_waiting_time(i, time_left);
					train->change_waiting_time(-delta);
					if (train->departure_time() <= _time)
						if (train->waiting_time() <= 0.0f)
						{
							if (train->index() != 0)
								train->journey()->output_file() << "             -----    The train start again    -----" << endl;
							train->start();
						}
				}
				else if (train->state() == e_train_state::stopping)
				{
					delta = 0;
					move_train(i, calc_distance_left(i));
				}
				else
				{
					delta = calc_run_time(i, time_left);
					train->run(delta);
				}

				move_train(i, ((old_speed + train->speed()) / 2.0f) * convert_minute_to_hour(delta));

				time_left -= delta;
				_time_travel[i] += delta;
				if (max_dist < _distance[i])
					max_dist = _distance[i];
			}
		}
	}
	_time += _time_delta;
}

void c_train_engine::run()
{
	if (_time == -1.0f || _time_delta == -1.0f)
		error_exit(1, "Bad engine configuration : Time [" + ftoa(_time, 2) + "] / Delta [" + ftoa(_time_delta, 2) + "]");
	if (_journey_list.size() == 0)
		return ;

	_time = 24 * 60;
	_time_travel.clear();
	_plot = new c_plot(Vector2(1280, 1080), Plot_data("Time"), Plot_data("Distance"));

	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		if (_time > _journey_list[i]->hour_panel()[0]->value())
			_time = _journey_list[i]->hour_panel()[0]->value();
		_plot->add_line(Color(0, 0, 0));
		_time_travel.push_back(_journey_list[i]->hour_panel()[0]->value());
		_journey_list[i]->calc_distance();

		if (_journey_list[i]->train() == nullptr)
			cout << "Bad" << endl;
		create_journey_output_file(_journey_list[i], _time);

		_journey_list[i]->train()->set_departure_time(_journey_list[i]->hour_panel()[0]->value());
		_journey_list[i]->train()->set_actual_rail(_journey_list[i]->get_rail(_journey_list[i]->train()->index()));
		_journey_list[i]->train()->actual_rail()->add_train(_journey_list[i]->train());
		_distance.push_back(0.0f);
		_arrived_hour.push_back(0.0f);
	}
	float old_time = _time;

	_arrived_train = 0;

	while (_arrived_train < _journey_list.size())
		iterate();

	create_journey_plot_output(_plot, old_time, _time, max_dist);

	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		string text = "Total distance for train [" + _journey_list[i]->name() + "] = " + ftoa(_distance[i], 3) + " and arrived at : [" + convert_hour_to_string(_arrived_hour[i]) + "] with " + convert_hour_to_string(_arrived_hour[i] - _journey_list[i]->hour_panel()[0]->value()) + " total travel time";
		_journey_list[i]->output_file() << text << endl;
		_journey_list[i]->close_output_file();
	}

	delete _plot;
}
