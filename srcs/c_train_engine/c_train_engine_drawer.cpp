#include "engine.h"

size_t c_train_engine::draw_train_information(size_t i)
{
	c_train* train = _journey_list[i]->train();
	string text;

	text.append(convert_hour_to_string(_time_travel[i]) + " : ");
	text.append("[" + train->state_str() + "]");
	text.append(" - [" + normalize_float(train->speed(), 0, '0', 3) + " km/h" + "]");
	text.append(" - [" + normalize_float(_distance[i], 1, '0', 7) + " km]");
	text.append(" - [" + normalize_float(calc_distance_left(i), 3, '0', 7) + " km]");
	text.append(" --> ");
	train->journey()->output_file() << text;

	return (text.size());
}

void c_train_engine::draw_train_position(size_t i)
{
	c_train* train = _journey_list[i]->train();
	string text;

	for (size_t j = 0; j < train->journey()->path().size() - 1; j++)
	{
		c_rail *rail = train->journey()->get_rail(j);
		size_t t = rail->train_list(e_way_type::even).size() + rail->train_list(e_way_type::odd).size();

		if (t == 1)
			if (rail->train_list(e_way_type::even).size() != 0)
				text = normalize_string(to_string(rail->train_list(e_way_type::even)[0]->num()), '0', 2);
			else
				text = normalize_string(to_string(rail->train_list(e_way_type::odd)[0]->num()), '0', 2);
		else
			text = (t == 0 ? "  " : "MM");

		train->journey()->output_file() << (j != 0 ? "-" : "") <<  "[" << text << "]";
	}

	train->journey()->output_file() << endl;
}

void c_train_engine::draw_train_state(size_t i)
{
	c_train* train = _journey_list[i]->train();
	size_t len = draw_train_information(i);
	draw_train_position(i);
}
