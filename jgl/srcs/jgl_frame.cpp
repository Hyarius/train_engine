#include "jgl.h"

using namespace std;

c_frame::c_frame(c_widget *p_parent, int p_border_size, Color p_front, Color p_back) : c_widget(p_parent)
{
	border_size = p_border_size;
	front = p_front;
	back = p_back;
}

void c_frame::set_color(Color p_front, Color p_back)
{
	front = p_front;
	back = p_back;
}

void c_frame::set_border_size(int p_border_size)
{
	border_size = p_border_size;
}

void c_frame::render_frame()
{
	fill_rectangle(_viewport, back, 0, _viewport->size());
	fill_rectangle(_viewport, front, border_size, _viewport->size() - border_size * 2);
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
