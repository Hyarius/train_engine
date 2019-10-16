#include "engine.h"

void c_map::start_calculation()
{
	calc_distance_ratio();
	_state = map_state::travel_definition;
	if (_journey != nullptr)
		delete _journey;

	_journey = new c_journey(this);
}

void c_map::calc_duration()
{
	// if (_path.size() < 2)
	// {
	// 	cout << "No path to run" << endl;
	// 	return ;
	// }
	//
	// float total_time = 0.0f; //express in hour
	//
	// for (size_t i = 0; i < _path.size() - 1; i++)
	// {
	// 	pair_milestone key = {_path[i], _path[i+1]};
	// 	c_rail *rail = _rails[key];
	// 	total_time += ((_path[i]->pos().distance(_path[i + 1]->pos()) * _scale_unit) / rail->speed()) * 60;
	// 	if (i != 0 && _path[i]->place() != nullptr)
	// 		total_time += static_cast<float>(_path[i]->place()->waiting_time());
	// }
	//
	// cout << "Total time : " << (int)(total_time) << endl;
}
