#include "engine.h"

size_t c_train_engine::draw_train_information(size_t i)
{
	c_train* train = _train_list[i];
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
	c_train* train = _train_list[i];
	string text;

	for (size_t j = 0; j < train->journey()->path().size() - 1; j++)
	{
		c_rail *rail = train->journey()->get_rail(j);
		size_t t = rail->train_list().size();

		if (t == 1)
			text = normalize_string(to_string(rail->train_list()[0]->num()), '0', 2);
		else
			text = (t == 0 ? "  " : "MM");

		train->journey()->output_file() << (j != 0 ? "-" : "") <<  "[" << text << "]";
	}

	train->journey()->output_file() << endl;
}

void c_train_engine::draw_rail_occupation(size_t first_len, size_t i)
{
	c_train* train = _train_list[i];
	string text;

	for (size_t tmp = 0; tmp < 3; tmp++)
	{
		text = string(first_len, ' ');
		e_channel_state type = static_cast<e_channel_state>(tmp);

		for (size_t j = 0; j < train->journey()->path().size() - 1; j++)
		{
			c_rail *rail = train->journey()->get_rail(j);

			if (j != 0)
				text.append("-");
			string tmp_text = to_string(rail->channel(type));
			while (tmp_text.size() < 2)
				tmp_text.insert(tmp_text.begin(), '0');
			text.append("[" + tmp_text + "]");
		}
		train->journey()->output_file() << text << endl;
	}
}

void c_train_engine::draw_train_state(size_t i)
{
	c_train* train = _train_list[i];
	train->journey()->output_file() << endl;
	size_t len = draw_train_information(i);
	draw_train_position(i);
	train->journey()->output_file() << endl;
	draw_rail_occupation(len, i);
}
