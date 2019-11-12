#include "engine.h"

c_train::c_train(c_journey *journey)
{
	_journey = journey;
	_speed = 0.0f;
	_old_speed = 0.0f;
	_acceleration = 0.0f;
	_deceleration = 0.0f;
	_slow_down_dist = 0.0f;
	_distance_per_tic = 0.0f;
	_state = e_train_state::waiting;
	_index = 0;
	_distance = 0.0f;
	_departure_time = 0.0f;
	_actual_rail = nullptr;
}

void c_train::calc_deceleration_dist(float target_speed)
{
	float deceleration_convert = convert_m_per_s2_to_km_per_h2(_deceleration);

	_slow_down_dist = (pow(target_speed, 2.0f) - pow(_speed, 2.0f)) / (2.0f * deceleration_convert);
}

void c_train::change_speed(float time, float target_speed)
{
	set_speed(target_speed);
	set_distance_per_tic(speed() * convert_minute_to_hour(time));
	calc_deceleration_dist(0);
}

void c_train::accelerate(float time)
{
	float convert_time = convert_minute_to_hour(time);


	_speed = _speed + (convert_m_per_s2_to_km_per_h2(_acceleration) * convert_time);

	set_distance_per_tic(_speed * convert_time);
	calc_deceleration_dist(0);
}

void c_train::decelerate(float time)
{
	float convert_time = convert_minute_to_hour(time);


	_speed = _speed + (convert_m_per_s2_to_km_per_h2(_deceleration) * convert_time);

	if (_speed != 0.0f)
		set_distance_per_tic(_speed * convert_time);
	calc_deceleration_dist(0);
}

void c_train::accelerate_to_speed(float time, float target_speed)
{
	accelerate(time);

	if (speed() > target_speed)
		change_speed(time, target_speed);
}

void c_train::decelerate_to_speed(float time, float target_speed)
{
	decelerate(time);

	if (speed() < target_speed)
		change_speed(time, target_speed);
}

void c_train::move_to_next_rail(c_map *map)
{
	actual_rail()->remove_train(this);
	set_waiting_time(0);
	set_distance(distance() - actual_rail()->distance());
	set_index(index() + 1);
	set_actual_rail(_journey->get_rail(map , index()));
	if (_journey->path()[index()]->place() != nullptr)
	{
		set_waiting_time(_journey->wait_entry()[index()]->value());
		if (waiting_time() != 0 || index() == _journey->path().size() - 1)
		{
			_journey->output_file() << "             -----    Arrived at " << _journey->path()[index()]->place()->name() << "    -----" << endl;
			if (waiting_time() != 0)
				_journey->output_file() << "             Need to wait until " << convert_hour_to_string(_journey->hour_panel()[index()]->value()) << " or " << ftoa(waiting_time(), 0) << "min" << endl;
			set_speed(0);
			set_state(e_train_state::waiting);
		}
	}
	if (actual_rail() != nullptr)
		actual_rail()->add_train(this);
}
