#ifndef C_CITY_H
#define C_CITY_H

#include "jgl.h"

class c_city
{
private:
	class c_map *_map;
	string _name;
	Vector2 _pos;
	int _selected;

public:
	c_city(class c_map *p_map, Vector2 p_pos = Vector2());

	string name(){return (_name);}
	void draw();
	bool clicked(Vector2 mouse);
	void select();
};

#endif
