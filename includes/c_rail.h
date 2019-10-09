#ifndef C_RAIL_H
#define C_RAIL_H

#include "jgl.h"

class c_rail
{
private:
	float _max_speed;
	Polygon2D *_poly;

public:
	c_rail(Vector2 pos1, Vector2 pos2);

	Polygon2D *poly(){return (_poly);}
};

#endif
