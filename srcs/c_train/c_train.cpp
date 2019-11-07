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
	float converted = _deceleration / 1000.0f; // m/s^2 -> km/s^2
	converted *= 60.0f * 60.0f * 60.0f * 60.0f; // km/s^2 -> km/h/2

	_slow_down_dist = ((pow(min_speed, 2.0f) - pow(_speed, 2.0f)) / (2.0f * converted));
}

// Time : minute - Speed : km/h - acceleration : m/s^-2
void c_train::accelerate(float time)
{
	time = time * 60;

	_speed = _speed + (_acceleration * time);

	calc_deceleration_dist(0);
}

void c_train::decelerate(float time)
{
	time = time * 60;

	_speed = _speed + (_deceleration * time);

	calc_deceleration_dist(0);
}
