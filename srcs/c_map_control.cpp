#include "engine.h"

bool c_map::handle_mouse()
{
	if (is_pointed(g_mouse->pos))
	{
		if (g_mouse->get_button(mouse_button::left) == mouse_state::down)
		{
			if (g_mouse->rel_pos != Vector2(0, 0))
			{
				_map_anchor = _map_anchor + g_mouse->rel_pos;
				return (true);
			}
		}
		if (g_mouse->get_button(mouse_button::left) == mouse_state::up)
		{
			if (g_mouse->motion == false)
			{
				if (_selected == nullptr)
				{
					c_city *result = check_city();
					if (result == nullptr)
						add_city();
					else
						select_city(result);
				}
				else
				{
					_selected->select();
					select_city(nullptr);
				}
				return (true);
			}
		}
	}

	if (g_mouse->wheel != 0)
	{
		float ratio_x;
		float ratio_y;

		ratio_x = (_map.size().x * _zoom) / _map_anchor.x;
		ratio_y = (_map.size().y * _zoom) / _map_anchor.y;

		if (g_mouse->wheel > 0)
			_zoom *= 1.2f;
		else
			_zoom *= 0.8f;

		_map_anchor.x = (_map.size().x * _zoom) / ratio_x;
		_map_anchor.y = (_map.size().y * _zoom) / ratio_y;

		return (true);

	}
	return (false);
}
