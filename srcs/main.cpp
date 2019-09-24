#include "engine.h"

using namespace std;

void tmp(Data data)
{
	cout << "here" << endl;
}

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(1240, 1080), Color(15, 15, 15));

	c_value_label label = c_value_label(1304596.564f);
	label.set_geometry(Vector2(150, 150), Vector2(500, 50));
	label.label().set_align(alignment::centred);
	label.label().set_color(text_color::dark_green);
	label.active();

	return (win.run());
}
