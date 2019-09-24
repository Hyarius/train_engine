#include "jgl.h"

w_check_component::w_check_component(
	Vector2 p_anchor, Vector2 p_area,
	bool p_state,
	Color p_back, Color p_front, Color p_check,
	int p_border)
{
	_anchor = p_anchor;
	_area = p_area;
	_border = p_border;
	_back = p_back;
	_front = p_front;
	_check = p_check;
	_state = p_state;
}

w_check_component::~w_check_component()
{

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
	fill_rectangle(viewport, _back, _anchor, _area);
	fill_rectangle(viewport, _front, _anchor + _area.x/10.0f, _area - _area.x/5.0f + 1);
	if (_state == true)
	{
		fill_rectangle(viewport, _check, _anchor + _area.x/4.0f, _area - _area.x/2.0f + 1);
	}
}
