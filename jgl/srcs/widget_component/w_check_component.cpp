#include "jgl.h"

w_check_component::w_check_component(bool p_state)
{
	_area = Vector2();
	_anchor = Vector2();
	_border = 3;
	_back = Color(150, 150, 150, 255);
	_front = Color(195, 195, 195, 255);
	_check = Color(60, 150, 255);
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
	fill_rectangle(viewport, _back, _anchor - viewport->anchor() , _area);
	fill_rectangle(viewport, _front, _anchor - viewport->anchor() + _area.x/10.0f, _area - _area.x/5.0f + 1);
	if (_state == true)
	{
		fill_rectangle(viewport, _check, _anchor - viewport->anchor() + _area.x/4.0f, _area - _area.x/2.0f + 1);
	}
}
