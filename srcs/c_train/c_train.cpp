#include "engine.h"

c_train::c_train(c_journey *journey)
{
	_journey = journey;
	_speed = 0.0f;
	_acceleration = 0.0f;
	_deceleration = 0.0f;
	_slow_down_dist = 0.0f;
	_distance_per_tic = 0.0f;
	_state = e_train_state::normal;
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
	{
		set_speed(target_speed);
		calc_deceleration_dist(0);
	}
}

void c_train::decelerate_to_speed(float time, float target_speed)
{
	decelerate(time);

	if (speed() < target_speed)
	{
		set_speed(target_speed);
		calc_deceleration_dist(0);
	}
}

void c_train::move_to_next_rail(c_map *map)
{
	set_waiting_time(0);
	set_distance(distance() - actual_rail()->distance());
	set_index(index() + 1);
	set_actual_rail(_journey->get_rail(map , index()));
	if (_journey->path()[index()]->place() != nullptr)
	{
		set_waiting_time(_journey->wait_entry()[index()]->value());
		if (waiting_time() != 0)
		{
			set_speed(0);
			set_state(e_train_state::waiting);
		}
	}
}
