#ifndef C_RAIL_H
#define C_RAIL_H

#include "jgl.h"


class c_rail
{
private:
	Vector2 _main_pos;
	float _speed;
	Polygon2D *_poly;

	int _nb_channel;

	bool _state;

public:
	c_rail(Vector2 pos1, Vector2 pos2);

	void set_state(bool new_state){_state = new_state;}
	bool state(){return (_state);}

	void set_speed(float new_speed){_speed = new_speed;}
	float speed(){return (_speed);}

	void set_main_pos(Vector2 new_main_pos){_main_pos = new_main_pos;}
	Vector2 main_pos(){return (_main_pos);}

	void set_nb_channel(float new_nb_channel){_nb_channel = new_nb_channel;}
	float nb_channel(){return (_nb_channel);}

	void set_poly(Polygon2D *new_poly){_poly = new_poly;}
	Polygon2D *poly(){return (_poly);}
};

#endif
