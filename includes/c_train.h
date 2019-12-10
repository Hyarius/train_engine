#ifndef C_TRAIN_H
#define C_TRAIN_H

#include "jgl.h"

enum class e_train_state
{
	starting = 0,
	normal = 1,
	speed_up = 2,
	speed_down = 3,
	slowing = 4,
	stopping = 5,
	braking = 6,
	waiting = 7
};

class c_train
{
private:
	c_journey *_journey;
	c_city *_place;
	int _num;

	e_train_state _state;
	float _speed;
	float _max_speed;
	float _old_speed;
	float _acceleration;
	float _deceleration;
	float _slow_down_dist;
	float _distance_per_tic;

	size_t _index;
	float _distance;
	int _departure_time;
	float _waiting_time;
	c_rail *_actual_rail;
	size_t _actual_channel;

public:
	c_train(c_journey *journey);

	float accelerate(float time);
	float decelerate(float time);
	float run(float time);
	void calc_deceleration_dist(float target_speed);
	void calc_distance_per_tic(float time);
	void move_to_next_rail();

	void set_place(c_city *p_place){_place = p_place;}
	void change_speed(float time, float target_speed);
	void set_speed(float p_speed){_speed = p_speed;}
	void set_max_speed(float p_max_speed){_max_speed = p_max_speed;}
	void set_old_speed(float p_old_speed){_old_speed = p_old_speed;}
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
	void set_num(size_t p_num) { _num = p_num; }
	void set_actual_channel(size_t p_actual_channel) { _actual_channel = p_actual_channel; }

	e_way_type get_way_type();
	c_rail *get_rail(size_t index);

	void start();
	c_city *place(){return (_place);}
	size_t num() { return (_num); }
	float waiting_time(){return (_waiting_time);}
	float speed_lost(float time){return ((convert_m_per_s2_to_km_per_h2(_deceleration) * convert_minute_to_hour(time)));}
	float speed_gain(float time){return ((convert_m_per_s2_to_km_per_h2(_acceleration) * convert_minute_to_hour(time)));}
	c_journey *journey(){return (_journey);}
	e_train_state state(){return (_state);}
	size_t index(){return (_index);}
	float speed(){return (_speed);}
	float max_speed(){return (_max_speed);}
	float old_speed(){return (_old_speed);}
	float distance_per_tic(){return (_distance_per_tic);}
	float distance(){return (_distance);}
	float acceleration(){return (_acceleration);}
	float deceleration(){return (_deceleration);}
	float slow_down_dist(){return (_slow_down_dist);}
	int departure_time(){return (_departure_time);}
	c_rail *actual_rail(){return (_actual_rail);}
	size_t actual_channel(){return (_actual_channel);}
	string state_str(){
		switch ( _state )
		{
			case e_train_state::starting :
				return (" Starting ");
			case e_train_state::normal :
				return ("  Normal  ");
			case e_train_state::speed_up :
				return (" Speed_up ");
			case e_train_state::speed_down :
				return ("Speed_down");
			case e_train_state::stopping :
				return (" Stopping ");
			case e_train_state::waiting :
				return ("  Waiting ");
			case e_train_state::slowing :
				return ("  Slowing ");
			default :
				return ("   Error  ");
		}
	}
};

#endif
