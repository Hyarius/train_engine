#include "engine.h"

void create_journey_output_file(c_journey *journey, float time)
{
	string name = journey->name();
	string num = ftoa(journey->train()->num(), 0);
	ostream &file = journey->output_file();

	journey->create_output_file();

	file << "Calculation for the travel [" << name << "] with the train num [" << num << "]" << endl;
	file << convert_hour_to_string(time) << " : ";
	file << "[" << "   STATE  " << "]";
	file << " - [" << "  SPEED " << "]";
	file << " - [" << " dist tot " << "]";
	file << " - [" << " dist left" << "]";
	file << endl;
}

void create_journey_plot_output(c_plot *plot, float start_time, float end_time, float max_dist)
{
	plot->set_ordinate_min(-10.0f);
	plot->set_absciss_min(start_time - 15.0f);
	plot->set_point_size(0);
	plot->set_absciss_precision(3);
	plot->set_ordinate_precision(3);

	plot->set_absciss_max(end_time + 15.0f);
	plot->set_ordinate_max(max_dist + 10.0f);
	plot->set_absciss_gap(15.0f);
	plot->set_ordinate_gap(10.0f);
	plot->set_absciss_funct(&convert_time_to_string_round);
	plot->set_size(Vector2(plot->absciss().range() * 10, 1200.0f));

	plot->initialize();
	plot->save("output.png");
}
