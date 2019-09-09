#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(1240, 1080), Color(70, 70, 70));

	c_map map = c_map("ressources/image/map.jpg");
	map.set_geometry(Vector2(10, 10), Vector2(910, 750));
	map.active();

	c_user_entry entry = c_user_entry();
	entry.set_geometry(Vector2(10, 10), Vector2(150, 25));
	entry.active();

	return (win.run());
}
