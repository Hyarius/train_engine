#include "engine.h"

void c_map::start_calculation(vector<c_journey *> journeys)
{
	calc_distance_ratio();

	for (size_t i = 0; i < journeys.size(); i++)
		calc_duration(journeys[i]);
}

// Speed : km/h		acceleration : m/s^-2 		time : hour
static float calc_acceleration_time(float actual_speed, float target_speed, float distance)
{
	return ((distance / ((actual_speed + target_speed) / 2.0f)) * 60);
}

static float calc_distance_over_time(float actual_speed, float target_speed, float acceleration)
{
	float converted = acceleration / 1000.0f; // m/s^2 -> km/s^2
	converted *= 60.0f * 60.0f * 60.0f * 60.0f; // km/s^2 -> km/h/2

	return (((pow(target_speed, 2.0f) - pow(actual_speed, 2.0f)) / (2.0f * converted)));
}

#define ACCELERATION 0.75f
#define DECELERATION -0.75f

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

	int base_time = convert_int_to_hour(to_calc->hour_panel()[0]->hour().value(), to_calc->hour_panel()[0]->minute().value());
	int time = base_time;

	cout << "Travel from [" << to_calc->path().front()->place()->name() << "] to [" << to_calc->path().back()->place()->name() << "], depart at " << to_calc->hour_panel()[0]->hour().text() << "h" << to_calc->hour_panel()[0]->minute().text() << endl;
	for (size_t i = 0; i < to_calc->path().size() - 1; i++)
	{
		pair_milestone key = {to_calc->path()[i], to_calc->path()[i+1]};
		c_rail *rail = _rails[key];

		//First part :
		first_dist = calc_distance_over_time(speed, rail->speed() * 0.9f, ACCELERATION);
		first_time = calc_acceleration_time(speed, rail->speed() * 0.9f, first_dist);
		speed = rail->speed() * 0.9f;
		time += first_time;

		// // Second part:
		if (to_calc->path()[i + 1]->place() != NULL && (to_calc->wait_entry()[i + 1]->entry().value() != 0 || i + 1 == to_calc->path().size() - 1))
		 	second_dist = calc_distance_over_time(speed, 0, DECELERATION);
		else
			second_dist = 0;
		second_time = calc_acceleration_time(speed, 0, second_dist);
		time += second_time ;

		//Normal part :
		int distance = to_calc->path()[i]->pos().distance(to_calc->path()[i + 1]->pos()) * _scale_unit - first_dist - second_dist;
		float time_to_travel = distance / speed * 60.0f + first_time + second_time;

		if (to_calc->path()[i]->place() != NULL)
			speed = 0;

		time += time_to_travel;

		if (i != 0 && to_calc->path()[i]->place() != nullptr)
		{
			cout << "-----\nArrived at [" << to_calc->path()[i]->place()->name() << "] at " << convert_hour_to_string(time) << "(" << to_calc->wait_entry()[i]->entry().text() << " min stop)" << endl;
	 		time += static_cast<float>(to_calc->wait_entry()[i]->entry().value());
			if (time < to_calc->hour_panel()[i]->value())
				time = to_calc->hour_panel()[i]->value();
			cout << "Depart from [" << to_calc->path()[i]->place()->name() << "] : " << convert_hour_to_string(time) << endl;
		}
	}
	cout << "-----\nArrived at [" << to_calc->path().back()->place()->name() << "] at " << convert_hour_to_string(time) << endl;
	cout << "Total travel time : " << convert_hour_to_string(time - base_time) << endl;
}
