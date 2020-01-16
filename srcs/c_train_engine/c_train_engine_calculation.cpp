#include "engine.h"

float max_dist;

bool c_train_engine::can_overtake(size_t index)
{
	c_train* train = _journey_list[index]->train();
	e_way_type type = train->get_way_type();


	if (train->actual_rail()->way_overtake(type) == true)
	{
		return (true);
	}
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
		if (dist > 0.01f && dist <= train->actual_rail()->cantonal_dist())
			return (!(can_overtake(train_index)));
	}

	return (false);
}

void c_train_engine::iterate(bool perturbation)
{
	// while (_time > 24 * 60)
	// 	_time -= 24 * 60;

	float time_left = 0;
	float delta;
	float dist;

	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		c_train* train = _journey_list[i]->train();

		if (train->actual_rail() != nullptr)
		{
			time_left = _time_delta;

			while (time_left > 0.0001f && train->actual_rail() != nullptr)
			{
				train->calc_distance_per_tic(time_left);

				intelligence(i);

				cout << convert_hour_to_string(_time) << " - [" << train->state_str() << "] - [" << _time << "]" << endl;

				if (_plot_bool == true && train->state() != e_train_state::starting)
					_plot->add_point(_time + (_time_delta - time_left), _distance[i], i);

				if (_text_bool == true && train->state() != e_train_state::starting)
					draw_train_state(i);

				float old_speed = train->speed();

				if (train->state() != e_train_state::starting)
				{
					delta = execution(i, time_left);
					if (_base_time_travel[i] != -1.0f)
						calc_event(i, delta);
					move_train(i, ((old_speed + train->speed()) / 2.0f) * convert_minute_to_hour(delta));
				}
				else
				{
					float time_to_wait = train->departure_time() - _time;
					delta = (time_left < time_to_wait ? time_left : time_to_wait);
				}

				time_left -= delta;
				_time_travel[i] += delta;
				if (max_dist < _distance[i])
					max_dist = _distance[i];
			}
		}
	}
	_time += _time_delta;
}

void c_train_engine::run(string result_path, int p_simulation_index, bool p_plot_bool, bool p_text_bool)
{
	if (_time == -1.0f || _time_delta == -1.0f)
		error_exit(1, "Bad engine configuration : Time [" + ftoa(_time, 2) + "] / Delta [" + ftoa(_time_delta, 2) + "]");
	if (_journey_list.size() == 0)
		return ;

	_time = 60 * 24;
	_simulation_index = p_simulation_index + 1;
	_plot_bool = p_plot_bool;
	_text_bool = p_text_bool;
	_time_travel.clear();
	_distance.clear();
	_arrived_hour.clear();

	if (_plot_bool == true)
		_plot = new c_plot(Vector2(1280, 1080), Plot_data("Time"), Plot_data("Distance"));

	if (_base_time_travel.size() != _journey_list.size())
	{
		_base_time_travel.resize(_journey_list.size());
		for (size_t i = 0; i < _base_time_travel.size(); i++)
			_base_time_travel[i] = -1.0f;
	}

	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		if (_plot_bool == true)
			_plot->add_line(Color(0, 0, 0));
		if (_time > _journey_list[i]->hour_panel()[0]->value())
			_time = _journey_list[i]->hour_panel()[0]->value();
		_journey_list[i]->calc_distance();
		_journey_list[i]->set_exist(_text_bool);

		_journey_list[i]->train()->set_num(i);
		_journey_list[i]->train()->set_departure_time(_journey_list[i]->hour_panel()[0]->value());
		_journey_list[i]->train()->set_state(e_train_state::starting);

		cout << "Set departure to " << _journey_list[i]->train()->departure_time() << endl;
			if (_time > _journey_list[i]->train()->departure_time())
				_time = _journey_list[i]->train()->departure_time();
		_journey_list[i]->train()->set_actual_rail(_journey_list[i]->get_rail(_journey_list[i]->train()->index()));
		_journey_list[i]->train()->actual_rail()->add_train(_journey_list[i]->train());
		_distance.push_back(0.0f);
		_time_travel.push_back(0);
		_arrived_hour.push_back(0.0f);
	}
	cout << "Here time = " << _time << endl;
	float old_time = _time;

	_arrived_train = 0;

	while (_arrived_train < _journey_list.size())
		iterate(true);

	bool print_plot = false;

	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		string text = "Total distance for train [" + _journey_list[i]->name() + "] = " + ftoa(_distance[i], 3) + " and arrived at : [" + convert_hour_to_string(_arrived_hour[i] + _journey_list[i]->hour_panel()[0]->value()) + "] with " + convert_hour_to_string(_arrived_hour[i]) + " total travel time\n";
		_journey_list[i]->output_text() += text;
		if (_arrived_hour[i] != _base_time_travel[i] || p_simulation_index == 0)
			print_plot = true;
		if (_text_bool == true && (_arrived_hour[i] != _base_time_travel[i] || p_simulation_index == 0))
		{
			create_journey_output_file(result_path + "/text result", _simulation_index, _journey_list[i], old_time);
			_journey_list[i]->print_output_file();
		}
		if (_base_time_travel[i] == -1.0f)
			_base_time_travel[i] = _arrived_hour[i];
	}

	if (_plot_bool == true && print_plot == true)
	{
		create_journey_plot_output(result_path + "/plot result", _simulation_index, _plot, old_time, _time, max_dist);
		delete _plot;
	}
}

bool c_train_engine::is_late(float time)
{
	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		if (is_late(i, time) == true)
			return (true);
	}
	return (false);
}

bool c_train_engine::is_late(size_t i, float time)
{
	if (time == 0.0f && _arrived_hour[i] > _journey_list[i]->hour_panel().back()->value() + time)
		return (true);
	else if (time != 0.0f && _arrived_hour[i] >= _journey_list[i]->hour_panel().back()->value() + time)
		return (true);
	return (false);
}
