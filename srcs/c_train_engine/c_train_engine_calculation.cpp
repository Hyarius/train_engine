#include "engine.h"

void c_train_engine::iterate()
{
	_time += _time_delta;
}

void c_train_engine::run()
{
	if (_time == -1.0f || _time_delta == -1.0f)
		error_exit(1, "Bad engine configuration : Time [" + ftoa(_time, 2) + "] / Delta [" + ftoa(_time_delta, 2) + "]");

	float min_speed = 0.0f;
	float max_speed = 140.0f;
	vector<float> distance;

	for (size_t i = 0; i < _train_list.size(); i++)
	{
		_train_list[i]->calc_acceleration_time(max_speed);
		distance.push_back(0.0f);
	}


	float target = _time + 60.0f;
	while (_time < target)
	{
		iterate();
		float tmp_dist;
		cout << "Time : " << convert_hour_to_string(_time) << " -> ";
		for (size_t i = 0; i < _train_list.size(); i++)
		{
			if (i != 0)
				cout << " - ";
			if (target - _time > 24.0f - _train_list[i]->speed_up_time())
			{
				_train_list[i]->accelerate(_time_delta, max_speed);
				_train_list[i]->calc_deceleration_time(min_speed);
			}
			else if (target - _time <= _train_list[i]->slow_down_time())
			{
				_train_list[i]->decelerate(_time_delta, 0.0f);
				_train_list[i]->calc_acceleration_time(max_speed);
			}
			cout << "Train [" << i << "] : " << _train_list[i]->speed() << " km/h -> ";
			tmp_dist = _train_list[i]->speed() * _time_delta / 60;
			cout << "dist : " << tmp_dist;
			distance[i] += tmp_dist;
		}
		cout << endl;
	}
	for (size_t i = 0; i < distance.size(); i++)
	cout << "Total distance for train [" << i << "] = " << distance[i] << endl;
}
