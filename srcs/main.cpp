#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(0.85f, 0.85f), Color(195, 195, 195));

	c_plot plot = c_plot();

	plot.set_margin(Vector2(40, 40));
	plot.set_point_size(1);
	plot.set_line_size(1);

	int len = 200;

	for (size_t len = 20; len <= 20000; len *= 10)
	{
		plot.clear();

		plot.set_absciss_min(-10);
		plot.set_absciss_max(len + 10);
		plot.divide_absciss(10);

		plot.set_ordinate_min(-len / 2);
		plot.set_ordinate_max(len / 2);

		float height = 2.0f;

		plot.add_line(Color(255, 0, 0));
		plot.add_line(Color(0, 153, 0));
		plot.add_line(Color(0, 0, 255));

		for (size_t i = 0; i < 3; i++)
		{
			float value = 0;
			for (float x = 0; x < len; x++)
			{
				plot.add_point(Vector2(x, value), i);

				int tmp = generate_nbr(0, 100) / 50;
				if (tmp == 0)
					value -= height;
				else
					value += height;
			}
		}

		plot.initialize();
		plot.draw();
		plot.save("test" + to_string(len) + ".png");
	}

	return (0);

	// c_main_window main_window;
	//
	// return (win.run());
}
