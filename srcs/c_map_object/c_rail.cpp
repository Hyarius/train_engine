#include "engine.h"

c_rail::c_rail(Vector2 pos1, Vector2 pos2)
{
	_main_pos = pos1;
	_distance = -1;
	_speed = 145.0f;
	_pos1 = pos1;
	_pos2 = pos2;

	_nb_channel = 1;

	_state = false;

	_poly = new Polygon2D(0);

	Vector2 start = 0;
	Vector2 end = pos2 - pos1;
	Vector2 trans = pos2.cross(pos1).normalize();

	Vector2 pos[4];

	pos[0] = start + (trans * 0.8f);
	pos[1] = start - (trans * 0.8f);
	pos[2] = end + trans * 0.8f;
	pos[3] = end - trans * 0.8f;

	for (int i = 0; i < 4; i++)
		_poly->add_point(pos[i]);

	_poly->add_side(0, 1);
	_poly->add_side(2, 0);
	_poly->add_side(1, 3);
	_poly->add_side(3, 2);
}
