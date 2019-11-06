#include "engine.h"

c_train_engine::c_train_engine()
{
	_time = -1.0f;
	_time_delta = -1.0f;
	_train_list.clear();
}

void c_train_engine::add_train(c_train *new_train)
{
	_train_list.push_back(new_train);
}
