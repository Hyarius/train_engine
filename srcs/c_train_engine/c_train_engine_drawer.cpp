#include "engine.h"

void c_train_engine::draw_train_information(size_t i)
{
	c_train* train = _train_list[i];
	string text;

	train->journey()->output_file() << convert_hour_to_string(_time) << " : ";

	text = normalize_float(train->speed(), 0, '0', 3);
	// text = ftoa(train->speed(), 0);
	// while (text.size() < 3)
	// 	text.insert(text.begin(), '0');

	train->journey()->output_file() << "[" << text << " km/h] ";

	float ratio_dist = (train->distance() * 100.0f) / train->actual_rail()->distance();

	if (train->waiting_time() > 0.0f || train->departure_time() > _time)
		text = " waiting ";
	else
	{
		text = ftoa(_distance[i], 1);
		while (text.size() < 6)
			text.insert(text.begin(), '0');
		text.append(" km");
	}

	train->journey()->output_file() << "[" << text << "] ";
}

void c_train_engine::draw_train_state(size_t i)
{
	c_train* train = _train_list[i];
	string text;

	train->journey()->output_file() << convert_hour_to_string(_time) << " : ";

	train->journey()->output_file() << "[" << train->state_str() << "]";

	train->journey()->output_file() << " - [" << normalize_float(train->speed(), 0, '0', 3) << " km/h" << "]";

	train->journey()->output_file() << " - [" << normalize_float(_distance[i], 1, '0', 7) << " km]";

	train->journey()->output_file() << " - [" << normalize_float(calc_distance_left(i), 3, '0', 7) << " km]";

	train->journey()->output_file() << " - [" << normalize_float(train->slow_down_dist(), 3, '0', 7) << " km]";

	train->journey()->output_file() << " - [" << normalize_float(train->distance_per_tic(), 3, '0', 7) << " km] --> ";

	for (size_t j = 0; j < train->journey()->path().size() - 1; j++)
	{
		c_rail *rail = train->journey()->get_rail(_map, j);
		size_t t = train->journey()->get_rail(_map, j)->train_list().size();

		if (t == 1)
			text = normalize_string(to_string(rail->train_list()[0]->num()), '0', 2);
		else
			text = (t == 0 ? "  " : "MM");

		train->journey()->output_file() << (j != 0 ? "-" : "") <<  "[" << text << "]";
	}
	train->journey()->output_file() << endl;
}
