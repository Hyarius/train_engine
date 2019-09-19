#include "jgl.h"

using namespace std;

c_window::c_window(c_widget *p_parent, Color p_back) : c_widget(p_parent)
{
	back = p_back;
}

void c_window::set_geometry(Vector2 p_anchor, Vector2 p_area)
{
	resize(p_anchor, p_area);
}

void c_window::set_color(Color p_color)
{
	back = p_color;
}

void c_window::render()
{
	_viewport->use();

	fill_rectangle(_viewport, back, 0, _viewport->size());
}

bool c_window::handle_keyboard()
{
	return(false);
}

bool c_window::handle_mouse()
{
	return(false);
}
