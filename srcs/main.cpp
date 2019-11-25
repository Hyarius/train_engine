#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(0.85f, 0.85f), Color(195, 195, 195));

	c_plot plot = c_plot();

	plot.set_margin(Vector2(40, 40));
	plot.set_absciss_min(-60);
	plot.set_absciss_max(60);
	plot.set_absciss_gap(5);

	for (float x = -70; x < 70; x++)
		plot.add_point(Vector2(x, pow(x, 2) / 50.0f));

	plot.initialize();
	plot.draw();
	plot.save("test.png");

	return (0);

	// c_main_window main_window;
	//
	// return (win.run());
}
