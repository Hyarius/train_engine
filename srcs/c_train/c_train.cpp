#include "engine.h"

c_train::c_train()
{
	_speed = 0.0f;
	_acceleration = 0.0f;
	_deceleration = 0.0f;
	_speed_up_time = 0.0f;
	_slow_down_time = 0.0f;
}

void c_train::calc_acceleration_time(float max_speed)
{
	_speed_up_time = (max_speed - _speed) / _acceleration / 60;
}

void c_train::calc_deceleration_time(float min_speed)
{
	_slow_down_time = (min_speed - _speed) / _deceleration / 60;
}

// Time : minute - Speed : km/h - acceleration : m/s^-2
void c_train::accelerate(float time, float max_speed)
{

	time = time * 60;

	_speed = _speed + (_acceleration * time);

	if (_speed > max_speed)
		_speed = max_speed;
}

void c_train::decelerate(float time, float max_speed)
{
	time = time * 60;

	_speed = _speed + (_deceleration * time);

	if (_speed < max_speed)
		_speed = max_speed;
}
