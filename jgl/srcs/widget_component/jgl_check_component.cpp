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

bool w_check_component::check(Vector2 point, Vector2 pos1, Vector2 pos2)
{
	if (point.x < pos1.x || point.x > pos2.x || point.y < pos1.y || point.y > pos2.y)
		return (false);
	return (true);
}

void w_check_component::render(c_viewport *viewport, Vector2 pos, Vector2 size)
{
	fill_rectangle(viewport, Color(130, 130, 130, 255), pos, size);
	fill_rectangle(viewport, Color(210, 210, 210, 255), pos + size.x/10.0f, size - size.x/5.0f + 1);
	if (_state == true)
	{
		fill_rectangle(viewport, Color(70, 140, 210, 255), pos + size.x/4.0f, size - size.x/2.0f + 1);
	}
}
