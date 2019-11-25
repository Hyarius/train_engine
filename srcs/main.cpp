#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(0.85f, 0.85f), Color(195, 195, 195));

	c_plot plot = c_plot();

	plot.set_margin(Vector2(40, 40));
	plot.set_point_size(3);
	plot.set_line_size(0);

	int len = 200;

	plot.set_absciss_min(-10);
	plot.set_absciss_max(len + 10);
	plot.divide_absciss(10);

	plot.set_ordinate_min(-len / 2);
	plot.set_ordinate_max(len / 2);

	float value = 0;
	int test[2];
	test[0] = 0;
	test[1] = 0;
	for (float x = 0; x < len; x++)
	{
		int tmp = generate_nbr(0, 100) / 50;
		if (tmp == 0)
		{
			test[0]++;
			value -= 1.0f;
		}
		else
		{
			test[1]++;
			value += 1.0f;
		}

		plot.add_point(Vector2(x, value));
	}

	plot.initialize();
	plot.draw();
	plot.save("test.png");

	printf("Face : %d\n", test[0]);
	printf("Pile : %d\n", test[1]);
	printf("Diff : %d\n", test[1] - test[0]);
	printf(" Val : %f\n", value);

	return (0);

	// c_main_window main_window;
	//
	// return (win.run());
}
