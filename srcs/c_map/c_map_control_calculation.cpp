#include "engine.h"

static void reset_distance(vector<c_milestone *> &to_clean)
{
	for (size_t i = 0; i < to_clean.size(); i++)
		to_clean[i]->set_distance(numeric_limits<float>::max());
}

static vector<c_milestone *> calc_shortest_path(c_milestone *target)
{
	vector<c_milestone *> result;
	vector<c_milestone *> to_calc;

	result.clear();
	to_calc.clear();
	to_calc.push_back(target);

	for (size_t i = 0; i < to_calc.size(); i++)
	{

	}

	return (result);
}

static void calc_distance(c_milestone *start, c_milestone *target)
{
	vector<c_milestone *> to_calc;

	to_calc.push_back(start);
	to_calc[0]->set_distance(0);

	for (size_t i = 0; i < to_calc.size(); i++)
	{
		vector<c_milestone *> links = to_calc[i]->links_to();
		for (size_t j = 0; j < links.size(); j++)
		{


			float tmp_dist = to_calc[i]->distance() + to_calc[i]->pos().distance(links[j]->pos());


			if (tmp_dist < links[j]->distance())
			{
				links[j]->set_distance(tmp_dist);
				to_calc.push_back(links[j]);
			}
		}
	}

	for (size_t i = 0; i < to_calc.size(); i++)
		cout << "node : " << to_calc[i] << " ==> Dist : " << to_calc[i]->distance() << endl;
}

vector<c_milestone *> c_map::calc_path(c_milestone *start, c_milestone *target)
{
	vector<c_milestone *> result;

	reset_distance(_milestones);
	calc_distance(start, target);

	cout << "----------" << endl;

	result = calc_shortest_path(target);

	return (result);
}

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
				_journey->path().push_back(target_milestone);
			else if (find(_journey->path().begin(), _journey->path().end(), target_milestone) == _journey->path().end())
			{
				c_milestone *actual = _journey->path().back();

				if (actual->is_accesible(target_milestone))
					_journey->path().push_back(target_milestone);
				else if (target_milestone->place() != nullptr)
				{
					vector<c_milestone *> tmp_path = calc_path(actual, target_milestone);

					cout << "Size : " << tmp_path.size() << endl;

					for (size_t i = 1; i < tmp_path.size(); i++)
						_journey->path().push_back(tmp_path[i]);
				}
			}
		}

		if (_journey->path().size() >= 2)
			calc_duration();
	}

	return (false);
}


//60km parcours a 30km/h -> distance / vitesse
