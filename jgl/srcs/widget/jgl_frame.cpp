#include "jgl.h"

using namespace std;

c_frame::c_frame(c_widget *p_parent, int p_border_size, Color p_back, Color p_front) : c_widget(p_parent)
{
	_border_size = p_border_size;
	_front = p_front;
	_back = p_back;
}

void c_frame::set_color(Color p_front, Color p_back)
{
	_front = p_front;
	_back = p_back;
}

void c_frame::set_border_size(int p_border_size)
{
	_border_size = p_border_size;
}

void c_frame::render_frame()
{
	fill_rectangle(_viewport, _back, 0, _viewport->size());
	fill_rectangle(_viewport, _front, _border_size, _viewport->size() - _border_size * 2);
}

void c_frame::render()
{
	_viewport->use();

	render_frame();
}

bool c_frame::handle_keyboard()
{
	return (false);
}

bool c_frame::handle_mouse()
{
	return (false);
}