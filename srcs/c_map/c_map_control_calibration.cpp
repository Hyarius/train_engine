#include "engine.h"

bool c_map::control_calibration()
{
	if (g_mouse->get_button(mouse_button::left) == mouse_state::up)
	{
		if (g_mouse->motion == false)
		{
			place_landmark(convert_to_map_coord(g_mouse->pos));
			if (_landmark1 != Vector2() && _landmark2 != Vector2())
				_state = e_map_state::normal;
			return (true);
		}
	}
	return (false);
}
