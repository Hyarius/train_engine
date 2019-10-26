#include "engine.h"

void c_map::start_calculation(vector<c_journey *> journeys)
{
	calc_distance_ratio();

	for (size_t i = 0; i < journeys.size(); i++)
		calc_duration(journeys[i]);
}

void c_map::calc_duration(c_journey *to_calc)
{
	int time = to_calc->hour_panel()[0]->hour().value() * 60 + to_calc->hour_panel()[0]->minute().value();

	for (size_t i = 0; i < to_calc->path().size() - 2; i++)
	{
		pair_milestone key = {to_calc->path()[i], to_calc->path()[i+1]};
		c_rail *rail = _rails[key];

		int distance = to_calc->path()[i]->pos().distance(to_calc->path()[i + 1]->pos()) * _scale_unit;
		int time_to_travel = distance / rail->speed() * 60.0f;

		time += time_to_travel;

		if (i != 0 && to_calc->path()[i]->place() != nullptr)
		{
	 		time += static_cast<float>(to_calc->path()[i]->place()->waiting_time());
			cout << "Time : " << time/60 << "h" << time%60 << endl;
		}
	}
	cout << "Time : " << time/60 << "h" << time%60 << endl;
}
