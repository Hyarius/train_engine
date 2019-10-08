#ifndef JGL_GEOMETRY_H
#define JGL_GEOMETRY_H

#include "jgl_vector.h"
#include "jgl_viewport.h"

using namespace std;

struct	Poly_side
{
	size_t index_vertices[2];
	Vector2	normale;

	Poly_side(size_t p_index1, size_t p_index2, Vector2 p_normale)
	{
		index_vertices[0] = p_index1;
		index_vertices[1] = p_index2;
		normale = p_normale;
	}
};

class Polygon2D
{
private:
	Vector2 _pos;

	vector<Vector2> _points;
	vector<Poly_side> _sides;

	bool clicked(Vector2 point);

public:
	Polygon2D(Vector2 p_pos = 0);

	void draw(c_viewport *viewport, Color p_color);
	void draw(c_viewport *viewport, Color p_color, Vector2 p_pos, float scale = 1.0f);

	void add_point(Vector2 p_point){_points.push_back(p_point);}
	void remove_point(size_t index){if (index < _points.size())_points.erase(_points.begin() + index);}

	void add_side(Poly_side p_side){_sides.push_back(p_side);}
	void add_side(size_t index1, size_t index2){
		_sides.push_back(Poly_side(index1, index2, _points[index1].cross(_points[index2])));
	}
	void remove_side(size_t index){if (index < _sides.size())_sides.erase(_sides.begin() + index);}

	void set_pos(Vector2 p_pos){_pos = p_pos;}

	Vector2 pos(){return (_pos);}
	vector<Vector2> &points(){return (_points);}
	vector<Poly_side> &faces(){return (_sides);}
};

#endif
