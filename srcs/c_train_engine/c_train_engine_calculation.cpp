#include "engine.h"

float c_train_engine::get_next_city_dist(size_t train_index)
{

}

float c_train_engine::get_next_slow     _dist(size_t train_index)
{

}

void c_train_engine::iterate()
{
	_time += _time_delta;
	float tmp_dist;
	cout << "Time : " << convert_hour_to_string(_time) << " -> ";
	for (size_t i = 0; i < _train_list.size(); i++)
	{
		if (i != 0)
			cout << " - ";

		if (_train_list[i]->actual_rail() == nullptr)
		{
			cout << "Train [" << i << "] : No rail";
		}
		else
		{
			cout << "Train [" << i << "] : " << _train_list[i]->speed() << " km/h -> ";
			tmp_dist = _train_list[i]->speed() * _time_delta / 60;

			if (_train_list[i]->speed() < _train_list[i]->actual_rail()->speed())
			{
				_train_list[i]->accelerate(_time_delta);
				if (_train_list[i]->speed() > _train_list[i]->actual_rail()->speed())
					_train_list[i]->set_speed(_train_list[i]->actual_rail()->speed());
			}
			else if (_train_list[i]->speed() > _train_list[i]->actual_rail()->speed())
				_train_list[i]->decelerate(_time_delta);
			_train_list[i]->add_distance(tmp_dist);
			if (_train_list[i]->distance() >= _train_list[i]->actual_rail()->distance())
			{
				_train_list[i]->set_distance(_train_list[i]->distance() - _train_list[i]->actual_rail()->distance());
				_train_list[i]->set_index(_train_list[i]->index() + 1);
				_train_list[i]->set_actual_rail(_journey_list[i]->get_rail(_map, _train_list[i]->index()));
			}
			cout << "dist : " << tmp_dist;
			_distance[i] += tmp_dist;
		}
	}
	cout << endl;
}

void c_train_engine::run()
{
	if (_time == -1.0f || _time_delta == -1.0f)
		error_exit(1, "Bad engine configuration : Time [" + ftoa(_time, 2) + "] / Delta [" + ftoa(_time_delta, 2) + "]");

	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		_train_list[i]->set_departure_time(_journey_list[i]->hour_panel()[0]->value());
		_train_list[i]->set_actual_rail(_journey_list[i]->get_rail(_map, _train_list[i]->index()));
		_distance.push_back(0.0f);
	}

	float target = _time + 60.0f;
	while (_time < target)
	{
		iterate();
	}
	for (size_t i = 0; i < _distance.size(); i++)
		cout << "Total distance for train [" << _journey_list[i]->name() << "] = " << _distance[i] << endl;
}
