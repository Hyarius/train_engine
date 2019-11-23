#include "jgl.h"

w_check_component::w_check_component(c_widget *p_owner, bool p_state) :
		w_component(p_owner), w_graphical_component()
{
	_area = Vector2();
	_anchor = Vector2();
	_border = 3;
	_back = Color(150, 150, 150, 255);
	_front = Color(195, 195, 195, 255);
	_check = Color(60, 150, 255);
	_state = p_state;
}

bool w_check_component::check(Vector2 point, Vector2 viewport_anchor)
{
	Vector2 pos1;
	Vector2 pos2;

	pos1 = viewport_anchor + _anchor;
	pos2 = pos1 + _area;

	if (point.x < pos1.x || point.x > pos2.x || point.y < pos1.y || point.y > pos2.y)
		return (false);
	return (true);
}

void w_check_component::render(c_viewport *viewport)
{
	Vector2 pos_1;
	Vector2 pos_2;

	fill_rectangle(_back, _anchor , _area, viewport);
	fill_rectangle(_front, _anchor + _border, _area - _border * 2, viewport);
	if (_state == true)
		fill_rectangle(_check, _anchor + _border * 2, _area - _border * 4, viewport);
}
