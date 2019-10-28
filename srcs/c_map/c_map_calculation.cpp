#include "engine.h"

void c_map::start_calculation(vector<c_journey *> journeys)
{
	calc_distance_ratio();

	for (size_t i = 0; i < journeys.size(); i++)
		calc_duration(journeys[i]);
}

// Speed : km/h		acceleration : m/s^-2 		time : hour
static float calc_acceleration_time(float actual_speed, float target_speed, float acceleration)
{
	float converted = acceleration / 1000.0f; // m/s^2 -> km/s^2
	converted += 60 * 60; // km/s^2 -> km/h^2

	return ((target_speed - actual_speed) / converted);
}

static float calc_distance_over_time(float time, float acceleration, float speed)
{
	float converted = acceleration / 1000.0f; // m/s^2 -> km/s^2
	converted += 60 * 60; // km/s^2 -> km/h^2

	return ((1/2 * converted * time) * (1/2 * converted * time) + speed * time);
}

#define ACCELERATION 0.75f
#define DECELERATION 0.75f

void c_map::calc_duration(c_journey *to_calc)
{
	/*
	1)calcul du temps a passer pour atteindre la vitesse max =>
						Vitesse_voulue = vitesse_de_base + acceleration * temps
						Vitesse_voulue - vitesse_de_base = acceleration * temps
						temps = (Vitesse_voulue - vitesse_de_base) / acceleration

	2) calcul de la distance parcourue dans ce temps d'acceleration =>
						Distance parcourue = (1/2 * acceleration * temps) ^ 2 + Vitesse_voulue * temps
	*/

	float speed = 0;
	float first_dist = 0.0f;
	float second_dist = 0.0f;
	float first_time = 0.0f;
	float second_time = 0.0f;

	int time = to_calc->hour_panel()[0]->hour().value() * 60 + to_calc->hour_panel()[0]->minute().value();

	cout << "Travel from [" << to_calc->path().front()->place()->name() << "] to [" << to_calc->path().back()->place()->name() << "], depart at " << to_calc->hour_panel()[0]->hour().text() << "h" << to_calc->hour_panel()[0]->minute().text() << endl;
	for (size_t i = 0; i < to_calc->path().size() - 1; i++)
	{
		pair_milestone key = {to_calc->path()[i], to_calc->path()[i+1]};
		c_rail *rail = _rails[key];

		// // First part :
		// first_time = calc_acceleration_time(speed, rail->speed() * 0.9f, ACCELERATION);
		// speed = rail->speed() * 0.9f;
		// first_dist = calc_distance_over_time(first_time, ACCELERATION, 0);
		// time += first_time;
		// //
		// // Second part:
		// if (to_calc->path()[i+1]->place() != NULL)
		// 	second_time = calc_acceleration_time(speed, 0, DECELERATION);
		// else
		// 	second_time = 0;
		// time += second_time;
		// second_dist = calc_distance_over_time(second_time, DECELERATION, speed);

		//Normal part :
		int distance = to_calc->path()[i]->pos().distance(to_calc->path()[i + 1]->pos()) * _scale_unit - first_dist - second_dist;
		int time_to_travel = distance / (rail->speed() * 0.9) * 60.0f + first_time + second_time;

		// if (to_calc->path()[i+1]->place() != NULL)
		// 	speed = 0;

		time += time_to_travel;

		if (i != 0 && to_calc->path()[i]->place() != nullptr)
		{
			cout << "-----\nArrived at [" << to_calc->path()[i]->place()->name() << "] at " << time/60 << "h" << time%60 << "(" << to_calc->wait_entry()[i]->entry().text() << " min stop)" << endl;
	 		time += static_cast<float>(to_calc->wait_entry()[i]->entry().value());
			cout << "Depart from [" << to_calc->path()[i]->place()->name() << "] : " << time/60 << "h" << time%60 << endl;
		}
	}
	cout << "-----\nArrived at [" << to_calc->path().back()->place()->name() << "] at " << time/60 << "h" << time%60 << endl << endl << endl;
}
