#include "engine.h"

int nb = 0;
float max_dist = 0;

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
	}
	else
		result = time_left;

	if (result == 0)
		train->set_state(e_train_state::stopping);

	return (result);
}

float c_train_engine::calc_accelerate_time(size_t index, float time_left)
{
	float result;

	c_train *train = _train_list[index];
	float rail_speed;

	rail_speed = train->actual_rail()->speed();

	if (train->speed() + train->speed_gain(time_left) > rail_speed)
	{
		float ratio = (rail_speed - train->speed()) / train->speed_gain(time_left);
		result = time_left * ratio;
		if (result == 0)
			train->set_state(e_train_state::normal);
	}
	else
		result = time_left;

	return (result);
}

float c_train_engine::calc_run_time(size_t index, float time_left)
{
	float result;

	c_train *train = _train_list[index];
	if (train->slow_down_dist() >= calc_distance_left(index) - train->distance_per_tic())
	{
		float dist_to_run;
		float ratio;

		dist_to_run = calc_distance_left(index) - train->slow_down_dist();
		ratio = dist_to_run / train->distance_per_tic();
		train->set_state(e_train_state::speed_down);
		result = time_left * ratio;
	}
	else
		result = time_left;

	return (result);
}

float c_train_engine::calc_waiting_time(size_t index, float time_left)
{
	float result;

	c_train *train = _train_list[index];

	if (time_left <= train->waiting_time())
		result = time_left;
	else
		result = train->waiting_time();

	return (result);
}

void c_train_engine::iterate()
{
	if (_time >= 60 * 24)
		_time -= 60 * 24;

	float time_left = 0;
	float delta;
	float dist;

	for (size_t i = 0; i < _train_list.size(); i++)
	{
		c_train* train = _train_list[i];

		if (_time_travel[i] < _time && train->actual_rail() != nullptr)
		{

			time_left = _time_delta;

			while (time_left > 0.0001f && train->actual_rail() != nullptr)
			{
				_plot.add_point(_time + (_time_delta - time_left), _distance[i], i);
				nb++;
				train->calc_distance_per_tic(time_left);
				draw_train_state(i);

				if (train->state() == e_train_state::waiting && train->waiting_time() <= 0.0f)
					train->set_state(e_train_state::starting);
				if (train->state() == e_train_state::starting && train->departure_time() <= _time)
					train->set_state(e_train_state::speed_up);
				if (calc_distance_left(i) <= 0.005f)
					train->set_state(e_train_state::stopping);

				//cout << "Here in " << train->state_str() << endl;
				float old_speed = train->speed();

				if (train->state() == e_train_state::speed_up)
				{
					delta = calc_accelerate_time(i, time_left);
					train->accelerate(delta);
				}
				else if (train->state() == e_train_state::speed_down)
				{
					delta = calc_decelerate_time(i, time_left);
					train->decelerate(delta);
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
							train->set_state(e_train_state::starting);
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

	_plot = c_plot(Vector2(1280, 1080), Plot_data("Time"), Plot_data("Distance"));

	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		if (_time > _journey_list[i]->hour_panel()[0]->value())
			_time = _journey_list[i]->hour_panel()[0]->value();
		_plot.add_line(Color(0, 0, 0));
		_time_travel.push_back(_journey_list[i]->hour_panel()[0]->value());
		_journey_list[i]->calc_distance(_map);
		_journey_list[i]->create_output_file();
		_journey_list[i]->output_file() << "Calculation for the travel [" << _journey_list[i]->name() << "] with the train num [" << _train_list[i]->num() << "]" << endl;

		_journey_list[i]->output_file() << convert_hour_to_string(_time) << " : ";
		_journey_list[i]->output_file() << "[" << "   STATE  " << "]";
		_journey_list[i]->output_file() << " - [" << "  SPEED " << "]";
		_journey_list[i]->output_file() << " - [" << " dist tot " << "]";
		_journey_list[i]->output_file() << " - [" << " dist left" << "]";
		_journey_list[i]->output_file() << endl;

		_train_list[i]->set_departure_time(_journey_list[i]->hour_panel()[0]->value());
		_train_list[i]->set_actual_rail(_journey_list[i]->get_rail(_map, _train_list[i]->index()));
		_train_list[i]->actual_rail()->add_train(_train_list[i]);
		_distance.push_back(0.0f);
		_arrived_hour.push_back(0.0f);
	}
	_plot.set_ordinate_min(-1.0f);
	_plot.set_absciss_min(_time - 15.0f);
	_plot.set_point_size(0);
	_plot.set_absciss_precision(3);
	_plot.set_ordinate_precision(3);

	_arrived_train = 0;

	while (_arrived_train < _journey_list.size())
		iterate();

	_plot.set_absciss_max(_time + 15.0f);
	_plot.set_ordinate_max(max_dist + 10.0f);
	_plot.set_absciss_gap(15.0f);
	_plot.set_ordinate_gap(10.0f);
	_plot.set_absciss_funct(&convert_hour_to_string);
	_plot.save("test.png");

	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		string text = "Total distance for train [" + _journey_list[i]->name() + "] = " + ftoa(_distance[i], 3) + " and arrived at : [" + convert_hour_to_string(_arrived_hour[i]) + "] with " + convert_hour_to_string(_arrived_hour[i] - _journey_list[i]->hour_panel()[0]->value()) + " total travel time";
		_journey_list[i]->output_file() << text << endl;
		_journey_list[i]->close_output_file();
	}
}
