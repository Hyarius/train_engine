#include "jgl.h"
#include "jgl_algorithm.h"

Polygon2D::Polygon2D(Vector2 p_pos)
{
	_pos = p_pos;
	_points.clear();
	_sides.clear();
}

void Polygon2D::draw(c_viewport *viewport, Color p_color)
{
	for (size_t i = 0; i < _sides.size(); i++)
	{
		Vector2 pos1, pos2;

		pos1 = _points[_sides[i].index_vertices[0]] + _pos;
		pos2 = _points[_sides[i].index_vertices[1]] + _pos;

		draw_line(viewport, p_color, pos1, pos2);
	}
}

void Polygon2D::draw(c_viewport *viewport, Color p_color, Vector2 p_pos, float scale)
{
	_pos = p_pos;

	for (size_t i = 0; i < _sides.size(); i++)
	{
		Vector2 pos1, pos2;

		pos1 = (_points[_sides[i].index_vertices[0]] * scale) + _pos;
		pos2 = (_points[_sides[i].index_vertices[1]] * scale) + _pos;

		draw_line(viewport, p_color, pos1, pos2);
	}
}

bool Polygon2D::clicked(Vector2 point)
{
	float value[4];

	for (size_t i = 0; i < this->_sides.size(); i++)
	{
		SAT_test(_sides[i].normale, _points, &(value[0]), &(value[1]));
		SAT_test(_sides[i].normale, {point}, &(value[2]), &(value[3]));

		if (!is_middle(value[0], value[1], value[2]) && !is_middle(value[2], value[3], value[0]))
			return (false);
	}

	return (true);
}
