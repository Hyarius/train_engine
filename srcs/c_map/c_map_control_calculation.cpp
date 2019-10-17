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
			if (_journey->path().size() == 0)
				_journey->add_point(target_milestone, pair_int(0, 0));
			else if (find(_journey->path().begin(), _journey->path().end(), target_milestone) == _journey->path().end())
			{
				c_milestone *actual = _journey->path().back();

				if (actual->is_accesible(target_milestone))
					_journey->path().push_back(target_milestone);
				else if (target_milestone->place() != nullptr)
				{
					vector<c_milestone *> tmp_path = calc_path(actual, target_milestone);

					for (int i = tmp_path.size() - 1; i >= 0; i--)
						_journey->add_point(tmp_path[i]);

				}
			}
			_journey->actualize_panel();
		}

		if (_journey->path().size() >= 2)
			calc_duration();
	}

	return (false);
}


//60km parcours a 30km/h -> distance / vitesse
