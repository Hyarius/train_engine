#include "engine.h"

int all_num = 0;

c_train::c_train(c_journey *journey)
{
	_journey = journey;
	_num = all_num;
	all_num++;
	_place = nullptr;
	_speed = 0.0f;
	_max_speed = 160.0f;
	_old_speed = 0.0f;
	_acceleration = 0.0f;
	_deceleration = 0.0f;
	_slow_down_dist = 0.0f;
	_distance_per_tic = 0.0f;
	_state = e_train_state::starting;
	_index = 0;
	_distance = 0.0f;
	_departure_time = 0.0f;
	_actual_rail = nullptr;
	_waiting_time = 0;
	_event_waiting_time = 0;

}

void c_train::calc_deceleration_dist(float target_speed)
{
	float deceleration_convert = convert_m_per_s2_to_km_per_h2(_deceleration);

	_slow_down_dist = (pow(target_speed, 2.0f) - pow(_speed, 2.0f)) / (-2.0f * deceleration_convert);
}

void c_train::calc_distance_per_tic(float time)
{
	set_distance_per_tic(_speed * convert_minute_to_hour(time));
}

void c_train::change_speed(float time, float target_speed)
{
	set_speed(target_speed);
	calc_distance_per_tic(time);
	calc_deceleration_dist(0);
}

float c_train::accelerate(float time)
{
	float convert_time = convert_minute_to_hour(time);
	float old;

	old = _speed;
	_speed = _speed + (convert_m_per_s2_to_km_per_h2(_acceleration) * convert_time);

	calc_distance_per_tic(time);
	calc_deceleration_dist(0);

	return (((old + _speed) / 2) * convert_time);
}

float c_train::decelerate(float time)
{
	float convert_time = convert_minute_to_hour(time);
	float old;

	old = _speed;
	_speed = _speed - (convert_m_per_s2_to_km_per_h2(_deceleration) * convert_time);

	calc_distance_per_tic(time);
	calc_deceleration_dist(0);

	return (((old + _speed) / 2) * convert_time);
}

float c_train::run(float time)
{
	float convert_time = convert_minute_to_hour(time);

	return (_speed * convert_time);
}

void c_train::move_to_next_rail()
{
	actual_rail()->remove_train(this);
	set_waiting_time(0);
	set_distance(distance() - actual_rail()->distance());
	set_index(index() + 1);
	set_actual_rail(_journey->get_rail(index()));
	if (_journey->path()[index()]->place() != nullptr)
	{
		set_waiting_time(_journey->wait_entry()[index()]->value());
		if (waiting_time() != 0 || index() == _journey->path().size() - 1)
		{
			if (_journey->exist() == true)
				_journey->output_text() += string("             -----    Arrived at ") + _journey->path()[index()]->place()->name() + string("    -----\n");
			if (waiting_time() != 0)
				if (_journey->exist() == true)
					_journey->output_text() += string("             Need to wait until ") + convert_hour_to_string(_journey->hour_panel()[index()]->value()) + string(" or ") + ftoa(waiting_time(), 0) + string("min\n");
			set_speed(0);
			if (state() != e_train_state::event)
				set_state(e_train_state::waiting);
		}
	}
	if (actual_rail() != nullptr)
		actual_rail()->add_train(this);
}

e_way_type c_train::get_way_type()
{
	return (e_way_type::even);
}


c_rail *c_train::get_rail(size_t index)
{
	if (_journey == nullptr)
		return (nullptr);
	return (_journey->get_rail(index));
}

void c_train::start()
{
	if (place() != nullptr)
		place()->remove_train_waiting();
	set_place(nullptr);
	set_state(e_train_state::normal);
}
