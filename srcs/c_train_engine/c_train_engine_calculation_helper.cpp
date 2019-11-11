#include "engine.h"

float c_train_engine::calc_distance_left(size_t index)
{
	size_t start_pos = _train_list[index]->index();
	float tmp;
	float result;

	result = 0;
	for (size_t i = start_pos; i < _journey_list[index]->path().size() - 1; i++)
	{

		c_rail *rail = _journey_list[index]->get_rail(_map, i);
		tmp = 0;
		if (rail != nullptr)
			tmp = rail->distance();

		result += tmp;

		if (_journey_list[index]->path()[i + 1]->place() != nullptr)
		{
			if (_journey_list[index]->wait_entry()[i + 1]->value() != 0)
				break ;
		}
	}
	result -= _train_list[index]->distance();
	return (result);
}
