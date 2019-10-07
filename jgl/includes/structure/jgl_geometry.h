#ifndef JGL_GEOMETRY_H
#define JGL_GEOMETRY_H

#include "jgl_vector.h"

using nmespace std;

struct	Face2D
{
	int index_vertices[3];
	Vector2	normale;
};

struct Polygon2D
{
	Vector2 pos;

	vector<Vector2> points;
	vector<Face2D> faces;
};

#endif
