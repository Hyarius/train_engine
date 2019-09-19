#include "jgl.h"

w_check_component::w_check_component(
		Vector2 p_anchor, Vector2 p_area,
		Color p_back, Color p_front, Color p_check,
		int p_border, bool p_state)
{
	_anchor = p_anchor;
	_area = p_area;
	_border = p_border;
	_back = p_back;
	_front = p_front;
	_check = p_check;
	_state = p_state;
}

w_check_component::~w_check_component()
{

}

void w_check_component::render(c_viewport *viewport)
{

}
