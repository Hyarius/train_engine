#include "engine.h"

#define MIN_SPEED 5.0f

float c_train_engine::calc_decelerate_time(size_t index, float time_left)
{
	float result;

	c_train *train = _train_list[index];
	float rail_speed;

	rail_speed = train->actual_rail()->speed();

	if (train->speed() + train->speed_lost(time_left) < MIN_SPEED)
	{
		float ratio = (MIN_SPEED - train->speed()) / train->speed_lost(time_left);
		result = time_left * ratio;
		if (result == 0)
			train->set_state(e_train_state::stopping);
	}
	else
		result = time_left;

	return (result);
}

float c_train_engine::calc_accelerate_time(size_t index, float time_left)
{
	float result;

	c_train *train = _train_list[index];
	float rail_speed;

	rail_speed = train->actual_rail()->speed();

	if (train->speed() + train->speed_gain(_time_delta) > rail_speed)
	{
		float ratio = (rail_speed - train->speed()) / train->speed_gain(_time_delta);
		result = time_left * ratio;
		if (result == 0)
			train->set_state(e_train_state::normal);
	}
	else
		result = time_left;

	return (result);
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

			time_left = _time_delta;

			while (time_left > 0.0f)
			{
				if (train->state() == e_train_state::waiting && train->waiting_time() <= 0.0f)
					train->set_state(e_train_state::starting);
				if (train->state() == e_train_state::starting && train->departure_time() <= _time)
					train->set_state(e_train_state::speed_up);
				if (train->state() != e_train_state::speed_down && train->slow_down_dist() >= calc_distance_left(i) - train->distance_per_tic())
					train->set_state(e_train_state::speed_down);
				if (train->state() == e_train_state::speed_down && calc_distance_left(i) <= 0.01f)
					train->set_state(e_train_state::stopping);

				cout << "Here in " << train->state_str() << endl;
				float old_speed = train->speed();

				if (train->state() == e_train_state::speed_up)
				{
					delta = calc_accelerate_time(i, time_left);
					if (delta != 0.0f)
					{
						train->accelerate(delta);
						train->calc_distance_per_tic(delta);
					}
				}
				else if (train->state() == e_train_state::speed_down)
				{
					delta = calc_decelerate_time(i, time_left);
					if (delta != 0.0f)
					{
						train->decelerate(delta);
						train->calc_distance_per_tic(delta);
					}
				}
				else if (train->state() == e_train_state::waiting)
				{
					delta = time_left;
					train->change_waiting_time(-delta);
					if (train->departure_time() <= _time)
						if (train->waiting_time() <= 0.0f)
						{
							train->set_state(e_train_state::speed_up);
							if (train->index() != 0)
								train->journey()->output_file() << "             -----    The train start again    -----" << endl;
						}
				}
				else
				{
					delta = time_left;
					if (delta != 0.0f)
					{
						train->run(delta);
						train->calc_distance_per_tic(delta);
					}
				}

				if (delta == 0)
					train->calc_distance_per_tic(delta);

				move_train(i, ((old_speed + train->speed()) / 2.0f) * convert_minute_to_hour(delta));

				time_left -= delta;
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
