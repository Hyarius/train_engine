#include "engine.h"

c_train::c_train()
{
	_speed = 0.0f;
	_acceleration = 0.0f;
	_deceleration = 0.0f;
	_slow_down_dist = 0.0f;

	_index = 0;
	_distance = 0.0f;
	_departure_time = 0.0f;
	_actual_rail = nullptr;
}

void c_train::calc_deceleration_dist(float min_speed)
{
	float tmp = convert_km_per_h_to_m_per_s(min_speed);
	float tmp2 = convert_km_per_h_to_m_per_s(_speed);
	float tmp3 = convert_m_per_s2_to_km_per_h2(_deceleration);

	_slow_down_dist = (pow(min_speed, 2.0f) - pow(_speed, 2.0f)) / (2.0f * tmp3);
}

void c_train::accelerate(float time)
{
	time = time / 60.0f;

	_speed = _speed + (convert_m_per_s2_to_km_per_h2(_acceleration) * time);

	calc_deceleration_dist(0);
}

void c_train::decelerate(float time)
{
	time = time / 60.0f;

	_speed = _speed + (convert_m_per_s2_to_km_per_h2(_deceleration) * time);

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
