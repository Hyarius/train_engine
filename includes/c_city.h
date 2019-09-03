#ifndef C_CITY_H
#define C_CITY_H

#include "jgl.h"

class c_city : public c_frame
{
private:
	class c_map *map;
	Vector2 pos;
	int selected;

public:
	c_city(c_widget *p_parent = nullptr, Vector2 p_pos = Vector2());
	void draw();
	bool clicked(Vector2 mouse);
	void select();
};

#endif
