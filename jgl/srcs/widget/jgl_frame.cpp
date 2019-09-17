#include "jgl.h"

using namespace std;

c_frame::c_frame(int p_border_size, Color p_back, Color p_front, c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(p_border_size, p_back, p_front);
}

void c_frame::set_color(Color p_back, Color p_front)
{
	_box.set_color(p_back, p_front);
}

void c_frame::set_border_size(int p_border_size)
{
	_box.set_border_size(p_border_size);
}

void c_frame::render()
{
	_viewport->use();

	_box.render(_viewport, 0, _viewport->size());
}

bool c_frame::handle_keyboard()
{
	return (false);
}

bool c_frame::handle_mouse()
{
	return (false);
}
