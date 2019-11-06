#ifndef C_TRAIN_ENGINE_H
#define C_TRAIN_ENGINE_H

#include "jgl.h"
#include "c_train.h"

class c_train_engine
{
private:
	float _time;
	float _time_delta;

	vector<c_train *>_train_list;

public:
	c_train_engine();

	void run();
	void iterate();

	void add_train(c_train *new_train);

	void set_time(int p_hour, int p_minute){_time = convert_int_to_hour(p_hour, p_minute);}
	void set_time(float p_time){_time = p_time;}
	void set_time_delta(float p_time_delta){_time_delta = p_time_delta;}

	float time(){return (_time);}
	float time_delta(){return (_time_delta);}
};

#endif
