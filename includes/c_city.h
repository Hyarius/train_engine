#ifndef C_CITY_H
#define C_CITY_H

#include "jgl.h"

class c_city
{
private:
	class c_map *map;
	string name;
	Vector2 pos;
	int selected;

public:
	c_city(class c_map *p_map, Vector2 p_pos = Vector2());
	void draw();
	bool clicked(Vector2 mouse);
	void select();
};

#endif
