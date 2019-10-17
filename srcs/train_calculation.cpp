#include "engine.h"

static void reset_distance(vector<c_milestone *> &to_clean)
{
	for (size_t i = 0; i < to_clean.size(); i++)
		to_clean[i]->set_distance(999);//numeric_limits<float>::max());
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
		c_milestone *next = nullptr;
		vector<c_milestone *> links = to_calc[i]->links();

		for (size_t j = 0; j < links.size(); j++)
		{
			
		}
	}

	return (result);
}

static void calc_distance(c_milestone *start)
{
	vector<c_milestone *> to_calc;

	to_calc.push_back(start);
	to_calc[0]->set_distance(0);

	for (size_t i = 0; i < to_calc.size(); i++)
	{
		float base_distance = to_calc[i]->distance();
		vector<c_milestone *> links = to_calc[i]->links();

		for (size_t j = 0; j < links.size(); j++)
		{
			float tmp = base_distance + to_calc[i]->pos().distance(links[j]->pos());

			if (tmp < links[j]->distance())
			{
				to_calc.push_back(links[j]);
				links[j]->set_distance(tmp);
			}
		}
	}
}

vector<c_milestone *> c_map::calc_path(c_milestone *start, c_milestone *target)
{
	vector<c_milestone *> result;

	reset_distance(_milestones);
	calc_distance(start);

	result = calc_shortest_path(target);

	return (result);
}
