#ifndef C_TRAIN_H
#define C_TRAIN_H

#include "jgl.h"

class c_train
{
private:
	float _speed;
	float _acceleration;
	float _deceleration;
	float _slow_down_dist;

	size_t _index;
	float _distance;
	int _departure_time;
	c_rail *_actual_rail;

public:
	c_train();

	void accelerate(float time);
	void decelerate(float time);
	void calc_deceleration_dist(float min_speed);

	void set_speed(float p_speed){_speed = p_speed;}
	void set_distance(float p_distance){_distance = p_distance;}
	void add_distance(float p_distance){_distance += p_distance;}
	void set_deceleration(float p_deceleration){_deceleration = p_deceleration;}
	void set_acceleration(float p_acceleration){_acceleration = p_acceleration;}
	void set_departure_time(int p_departure_time){_departure_time = p_departure_time;}
	void set_actual_rail(c_rail *p_actual_rail){_actual_rail = p_actual_rail;}
	void set_index(size_t p_index){_index = p_index;}

	size_t index(){return (_index);}
	float speed(){return (_speed);}
	float distance(){return (_distance);}
	float acceleration(){return (_acceleration);}
	float deceleration(){return (_deceleration);}
	float slow_down_dist(){return (_slow_down_dist);}
	int departure_time(){return (_departure_time);}
	c_rail *actual_rail(){return (_actual_rail);}
};

#endif
