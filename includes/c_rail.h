#ifndef C_RAIL_H
#define C_RAIL_H

#include "jgl.h"
#include "c_milestone.h"

enum class e_channel_state
{
	empty = 0,
	even = 1,
	odd = 2,
	error = 3
};

class c_rail
{
private:
	float _speed;
	Polygon2D *_poly;

	vector<class c_train *> _train_list;

	vector<e_channel_state> _channel;
	float _cantonal_dist;

	c_milestone *_pos1;
	c_milestone *_pos2;
	float _distance;

	bool _state;

public:
	c_rail(c_milestone *pos1, c_milestone *pos2);

	void add_train(class c_train *p_train);
	void remove_train(class c_train *p_train);

	void set_state(bool new_state){_state = new_state;}
	void set_nb_channel(size_t index){_channel.resize(index + 1);}
	void set_channel_state(size_t index, e_channel_state p_state){if (_channel.size() <= index)_channel.resize(index + 1);_channel[index] = p_state;}
	void set_cantonal_dist(float new_cantonal_dist){_cantonal_dist = new_cantonal_dist;}
	void set_pos1(c_milestone *new_pos1){_pos1 = new_pos1;}
	void set_pos2(c_milestone *new_pos2){_pos2 = new_pos2;}
	void calc_distance(float p_ratio){_distance = _pos1->pos().distance(_pos2->pos()) * p_ratio;}
	void set_speed(float new_speed){_speed = new_speed;}

	bool state(){return (_state);}
	float cantonal_dist(){return (_cantonal_dist);}
	c_milestone *pos1(){return (_pos1);}
	c_milestone *pos2(){return (_pos2);}
	float distance(){return (_distance);}
	float speed(){return (_speed);}
	size_t nb_channel(){return (_channel.size());}

	vector<e_channel_state> &channel(){return (_channel);}
	e_channel_state channel_state(size_t index){if (_channel.size() >= index)return (e_channel_state::error);return (_channel[index]);}
	vector<class c_train *> &train_list(){return (_train_list);}

	void set_poly(Polygon2D *new_poly){_poly = new_poly;}
	Polygon2D *poly(){return (_poly);}
};

#endif
