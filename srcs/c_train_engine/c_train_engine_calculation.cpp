#include "engine.h"

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

			while (time_left < _time_delta)
			{
				if (train->state() == e_train_state::waiting && train->waiting_time() <= 0.0f)
					train->set_state(e_train_state::starting);
				if (train->state() == e_train_state::starting && train->departure_time() <= _time)
					train->set_state(e_train_state::speed_up);

				cout << "Here in " << train->state_str() << endl;

				delta = _time_delta / 10.0f;

				time_left += delta;
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
