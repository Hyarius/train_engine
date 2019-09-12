#include "jgl.h"

w_check_component::w_check_component()
{
	_state = false;
}

bool w_check_component::state()
{
	return (_state);
}

void w_check_component::set_state(bool p_state)
{
	_state = p_state;
}

void w_check_component::render(c_viewport *viewport, Vector2 pos, Vector2 size)
{
	if (_state == true)
	{
		fill_rectangle(viewport, Color(66, 135, 245, 255), pos, size);
	}
}
