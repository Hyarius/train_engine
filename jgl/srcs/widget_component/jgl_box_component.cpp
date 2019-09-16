#include "jgl.h"

w_box_component::w_box_component(int p_border_size, Color p_back, Color p_front)
{
	_border_size = p_border_size;
	_back = p_back;
	_front = p_front;
}

void w_box_component::set_color( Color p_back, Color p_front)
{
	_back = p_back;
	_front = p_front;
}

int w_box_component::border_size()
{
	return (_border_size);
}

void w_box_component::set_border_size(int p_border_size)
{
	_border_size = p_border_size;
}

void w_box_component::render(c_viewport *viewport, Vector2 pos, Vector2 size, Color delta)
{
	fill_rectangle(viewport, _back + delta, 0, viewport->size());
	fill_rectangle(viewport, _front + delta, _border_size, viewport->size() - _border_size * 2);
}
