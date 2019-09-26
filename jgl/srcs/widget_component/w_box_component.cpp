#include "jgl.h"

w_box_component::w_box_component()
{
	_anchor = Vector2();
	_area = Vector2();
	_border = 3;
	_back = Color(150, 150, 150, 255);
	_front = Color(195, 195, 195, 255);
}

w_box_component::~w_box_component()
{

}

void w_box_component::render(c_viewport *viewport, Color delta)
{
	fill_rectangle(viewport, _back + delta, _anchor - viewport->anchor(), viewport->size());
	fill_rectangle(viewport, _front + delta, _anchor - viewport->anchor() + _border, viewport->size() - _border * 2);
}
