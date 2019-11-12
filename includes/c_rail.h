#ifndef C_RAIL_H
#define C_RAIL_H

#include "jgl.h"


class c_rail
{
private:
	Vector2 _main_pos;
	float _speed;
	Polygon2D *_poly;

	vector<class c_train *> _train_list;

	int _nb_channel;
	float _cantonal_dist;

	Vector2 _pos1;
	Vector2 _pos2;
	float _distance;

	bool _state;

public:
	c_rail(Vector2 pos1, Vector2 pos2);

	void add_train(class c_train *p_train);
	void remove_train(class c_train *p_train);

	void set_state(bool new_state){_state = new_state;}
	bool state(){return (_state);}

	void set_cantonal_dist(float new_cantonal_dist){_cantonal_dist = new_cantonal_dist;}
	float cantonal_dist(){return (_cantonal_dist);}

	void set_pos1(Vector2 new_pos1){_pos1 = new_pos1;}
	Vector2 pos1(){return (_pos1);}

	void set_pos2(Vector2 new_pos2){_pos2 = new_pos2;}
	Vector2 pos2(){return (_pos2);}

	void calc_distance(float p_ratio){_distance = _pos1.distance(_pos2) * p_ratio;}
	float distance(){return (_distance);}

	void set_speed(float new_speed){_speed = new_speed;}
	float speed(){return (_speed);}

	void set_main_pos(Vector2 new_main_pos){_main_pos = new_main_pos;}
	Vector2 main_pos(){return (_main_pos);}

	void set_nb_channel(float new_nb_channel){_nb_channel = new_nb_channel;}
	float nb_channel(){return (_nb_channel);}

	vector<class c_train *> &train_list(){return (_train_list);}

	void set_poly(Polygon2D *new_poly){_poly = new_poly;}
	Polygon2D *poly(){return (_poly);}
};

#endif
