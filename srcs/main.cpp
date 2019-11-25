#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(0.85f, 0.85f), Color(195, 195, 195));

	c_plot plot = c_plot();

	plot.set_margin(Vector2(40, 40));

	plot.initialize();
	plot.draw();
	plot.save("test.png");

	return (0);

	// c_main_window main_window;
	//
	// return (win.run());
}
