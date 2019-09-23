#include "jgl.h"

c_button::c_button(c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component();
	_text = w_text_component("Click me !");
}

c_button::~c_button()
{

}

void c_button::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{

}

void c_button::render()
{

}

bool c_button::handle_mouse()
{
	return (false);
}

bool c_button::handle_keyboard()
{
	return (false);
}
