#include "engine.h"

c_train_engine::c_train_engine(c_map *p_map)
{
	_map = p_map;
	_time = -1.0f;
	_time_delta = -1.0f;
	clean();
}

void c_train_engine::add_journey(c_journey *new_journey, c_train *new_train)
{
	if (new_journey == nullptr)
		return ;

	if (new_train == nullptr)
	{
		new_train = new c_train(new_journey);
		new_train->set_acceleration(0.75f);
		new_train->set_deceleration(-0.75f);
	}

	_journey_list.push_back(new_journey);
	_train_list.push_back(new_train);
}

void c_train_engine::clean()
{
	_train_list.clear();
	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		delete _journey_list[i];
	}
	_journey_list.clear();
	_distance.clear();
}
