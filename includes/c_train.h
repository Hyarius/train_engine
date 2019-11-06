#ifndef C_TRAIN_H
#define C_TRAIN_H

#include "jgl.h"

class c_train
{
private:
	float _speed;
	float _acceleration;
	float _deceleration;
	float _speed_up_time;
	float _slow_down_time;

public:
	c_train();

	void accelerate(float time, float max_speed);
	void decelerate(float time, float max_speed);
	void calc_acceleration_time(float max_speed);
	void calc_deceleration_time(float min_speed);

	void set_speed(float p_speed){_speed = p_speed;}
	float speed(){return (_speed);}

	void set_acceleration(float p_acceleration){_acceleration = p_acceleration;}
	float acceleration(){return (_acceleration);}

	void set_deceleration(float p_deceleration){_deceleration = p_deceleration;}
	float deceleration(){return (_deceleration);}

	void set_speed_up_time(float p_speed_up_time){_speed_up_time = p_speed_up_time;}
	float speed_up_time(){return (_speed_up_time);}

	void set_slow_down_time(float p_slow_down_time){_slow_down_time = p_slow_down_time;}
	float slow_down_time(){return (_slow_down_time);}
};

#endif
