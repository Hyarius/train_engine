#include "jgl.h"

w_box_component::w_box_component(Vector2 p_anchor, Vector2 p_area,
			int p_border, Color p_back, Color p_front)
{
	_anchor = p_anchor;
	_area = p_area;
	_border = p_border;
	_back = p_back;
	_front = p_front;
}

w_box_component::~w_box_component()
{

}

void w_box_component::render(c_viewport *viewport)
{
	fill_rectangle(viewport, _back, 0, viewport->size());
	fill_rectangle(viewport, _front, _border, viewport->size() - _border * 2);
}
