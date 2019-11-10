#ifndef C_TRAIN_H
#define C_TRAIN_H

#include "jgl.h"

enum class e_train_state
{
	normal = 0,
	speed_up = 1,
	first_slow_down = 2,
	slow_down = 3,
	waiting = 4
};

class c_train
{
private:
	c_journey *_journey;

	e_train_state _state;
	float _speed;
	float _acceleration;
	float _deceleration;
	float _slow_down_dist;
	float _distance_per_tic;

	size_t _index;
	float _distance;
	int _departure_time;
	float _waiting_time;
	c_rail *_actual_rail;

public:
	c_train(c_journey *journey);

	void accelerate(float time);
	void accelerate_to_speed(float time, float target_speed);
	void decelerate(float time);
	void decelerate_to_speed(float time, float target_speed);
	void calc_deceleration_dist(float target_speed);
	void move_to_next_rail(c_map *map);

	void change_speed(float time, float target_speed){
		set_speed(target_speed);
		calc_deceleration_dist(0);
		set_distance_per_tic(speed() * convert_minute_to_hour(time));
	}
	void set_speed(float p_speed){_speed = p_speed;}
	void set_distance_per_tic(float p_distance_per_tic){_distance_per_tic = p_distance_per_tic;}
	void set_state(e_train_state p_state){_state = p_state;}
	void set_distance(float p_distance){_distance = p_distance;}
	void add_distance(float p_distance){_distance += p_distance;}
	void set_deceleration(float p_deceleration){_deceleration = p_deceleration;}
	void set_acceleration(float p_acceleration){_acceleration = p_acceleration;}
	void set_departure_time(int p_departure_time){_departure_time = p_departure_time;}
	void set_actual_rail(c_rail *p_actual_rail){_actual_rail = p_actual_rail;}
	void set_index(size_t p_index){_index = p_index;}
	void set_waiting_time(float p_waiting_time){_waiting_time = p_waiting_time;}
	void change_waiting_time(float delta){_waiting_time += delta;}

	float waiting_time(){return (_waiting_time);}
	c_journey *journey(){return (_journey);}
	e_train_state state(){return (_state);}
	size_t index(){return (_index);}
	float speed(){return (_speed);}
	float distance_per_tic(){return (_distance_per_tic);}
	float distance(){return (_distance);}
	float acceleration(){return (_acceleration);}
	float deceleration(){return (_deceleration);}
	float slow_down_dist(){return (_slow_down_dist);}
	int departure_time(){return (_departure_time);}
	c_rail *actual_rail(){return (_actual_rail);}
};

#endif
