#include "engine.h"

bool c_map::control_travel_definition()
{
	if (_cities.size() < 2)
	{
		_state = map_state::normal;
		return (false);
	}

	if (g_mouse->get_button(mouse_button::left) == mouse_state::up)
	{
		c_city *target_city = check_city();
		c_milestone *target_milestone;

		if (target_city != nullptr)
			target_milestone = target_city->milestone();
		else
			target_milestone = check_milestone();

		if (target_milestone != nullptr)
		{
			if (_path.size() == 0 || _path[_path.size() - 1]->is_accesible(target_milestone))
				_path.push_back(target_milestone);
		}

		if (_path.size() >= 2)
			calc_duration();
	}

	return (false);
}


//60km parcours a 30km/h -> distance / vitesse
