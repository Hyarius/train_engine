#include "engine.h"

c_train_engine::c_train_engine()
{
	_time = -1.0f;
	_time_delta = -1.0f;
	clean();
}

void c_train_engine::add_journey(c_journey *new_journey)
{
	if (new_journey == nullptr)
		return ;
		
	_journey_list.push_back(new_journey);
}

void c_train_engine::clean()
{
	for (size_t i = 0; i < _journey_list.size(); i++)
	{
		delete _journey_list[i];
	}
	_journey_list.clear();
	_distance.clear();
}
