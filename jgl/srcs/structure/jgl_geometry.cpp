#include "jgl.h"

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

		cout << "Line : " << pos1 << "/ " << pos2 << endl;
		draw_line(viewport, p_color, pos1, pos2);
	}
}
