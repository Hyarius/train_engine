#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(1240, 1080), Color(15, 15, 15));

	c_frame label = c_frame();
	label.set_geometry(Vector2(150, 150), Vector2(300, 50));
	label.active();

	return (win.run());
}
