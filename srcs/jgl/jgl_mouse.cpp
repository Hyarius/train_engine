#include "jgl.h"

t_mouse *mouse;

s_mouse::s_mouse()
{
	old_pos = Vector2();
	pos = Vector2();
	rel_pos = Vector2(0, 0);
	button[MOUSE_LEFT] = false;
	button[MOUSE_RIGHT] = false;
	button[MOUSE_MIDDLE] = false;
}

void		s_mouse::actualize_mouse(SDL_Event *event)
{
	int x, y;
	Uint32 mousestate;

	old_pos = pos;
	mousestate = SDL_GetMouseState(&(x), &(y));
	pos = Vector2(x, y);
	if (old_pos.x != -1)
		rel_pos = pos - old_pos;

	if (event != NULL && event->type == SDL_MOUSEWHEEL)
		wheel = event->wheel.y;
	else
		wheel = 0.0f;

	cout << "Wheel = " + to_string(wheel) << endl;

	button[MOUSE_LEFT] = (mousestate & SDL_BUTTON(SDL_BUTTON_LEFT) ? true : false);
	button[MOUSE_RIGHT] = (mousestate & SDL_BUTTON(SDL_BUTTON_RIGHT) ? true : false);
	button[MOUSE_MIDDLE] = (mousestate & SDL_BUTTON(SDL_BUTTON_MIDDLE) ? true : false);

	if (old_pos != Vector2())
		rel_pos = pos - old_pos;
}

int			s_mouse::get_button(int type)
{
	if (type < MOUSE_RIGHT || type > MOUSE_MIDDLE)
		return (-1);
	return (button[type]);
}
