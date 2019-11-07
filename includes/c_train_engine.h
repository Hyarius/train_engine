#ifndef C_TRAIN_ENGINE_H
#define C_TRAIN_ENGINE_H

#include "jgl.h"

class c_train_engine
{
private:
	c_map *_map;

	float _time;
	float _time_delta;

	vector<c_journey *> _journey_list;
	vector<c_train *>_train_list;
	vector<float> _distance;

public:
	c_train_engine(c_map *p_map);

	void clean();
	void run();
	void iterate();

	void add_journey(c_journey *new_journey, c_train *new_train = nullptr);

	void set_map(c_map *p_map){_map = p_map;}
	void set_time(int p_hour, int p_minute){_time = convert_int_to_hour(p_hour, p_minute);}
	void set_time(float p_time){_time = p_time;}
	void set_time_delta(float p_time_delta){_time_delta = p_time_delta;}

	float time(){return (_time);}
	c_map *map(){return (_map);}
	float time_delta(){return (_time_delta);}
	vector<float> &distance(){return (_distance);}
};

#endif
