#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(1240, 1080), Color(70, 70, 70));

	// c_map map = c_map("ressources/image/map.jpg");
	// map.set_geometry(Vector2(10, 10), Vector2(910, 750));
	// map.active();

	c_user_entry entry = c_user_entry();
	entry.set_geometry(Vector2(10, 10), Vector2(150, 20));
	entry.active();

	c_text_label label = c_text_label();
	label.set_geometry(Vector2(10, 40), Vector2(300, 40));
	label.set_text("Ceci est un test");
	label.set_format(DARK_BLUE, UNDERLINE);
	label.active();

	c_text_label label2 = c_text_label();
	label2.set_geometry(Vector2(10, 100), Vector2(150, 20));
	label2.set_text("Ceci est un test");
	label2.active();

	return (win.run());
}
