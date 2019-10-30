#include "engine.h"

bool c_map::control_mouvement()
{
	if (g_mouse->get_button(mouse_button::left) == mouse_state::down)
	{
		if (_mile_selected != nullptr)
			return (false);
		if (g_mouse->rel_pos != Vector2(0, 0))
		{
			_map_anchor = _map_anchor + g_mouse->rel_pos;
			if (_journey != nullptr)
				_journey->actualize_panel();
			return (true);
		}
	}
	return (false);
}

bool c_map::control_zoom()
{
	if (g_mouse->wheel != 0)
	{
		float ratio_x;
		float ratio_y;

		ratio_x = (_map->size().x * _zoom) / _map_anchor.x;
		ratio_y = (_map->size().y * _zoom) / _map_anchor.y;

		if (g_mouse->wheel > 0 && _zoom * 1.2 <= 20.0f)
			_zoom *= 1.2f;
		else if (g_mouse->wheel < 0 && _zoom * 0.8f >= 0.5f)
			_zoom *= 0.8f;

		_map_anchor.x = (_map->size().x * _zoom) / ratio_x;
		_map_anchor.y = (_map->size().y * _zoom) / ratio_y;

		if (_journey != nullptr)
			_journey->actualize_panel();

		return (true);
	}
	return (false);
}
