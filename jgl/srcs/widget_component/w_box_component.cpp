#include "jgl.h"

w_box_component::w_box_component(c_widget *p_owner) :
		w_component(p_owner), w_graphical_component()
{
	_anchor = Vector2();
	_area = Vector2();
	_border = 3;
	_delta = Color(0, 0, 0, 0);
	_back = Color(150, 150, 150, 255);
	_front = Color(195, 195, 195, 255);
}

void w_box_component::render(c_viewport *viewport)
{
	if (_owner == NULL)
		return ;

	fill_rectangle(_back + _delta, _anchor , _area, viewport);
	fill_rectangle(_front + _delta, _anchor + _border, _area - _border * 2, viewport);
}
