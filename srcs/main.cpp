#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(1240, 1080), Color(15, 15, 15));

	c_value_label label = c_value_label(
			150.0f, 3,
			Color(150, 150, 150, 255),
			Color(195, 195, 195, 255));
	label.set_geometry(Vector2(50, 50), Vector2(350, 50));
	label.set_text_color(DARK_RED);
	label.set_alignment(alignment::right);
	label.active();

	return (win.run());
}
