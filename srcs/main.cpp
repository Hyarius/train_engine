#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(1240, 1080), Color(15, 15, 15));

	c_check_box label = c_check_box();
	label.set_geometry(Vector2(50, 50), Vector2(550, 20));
	label.set_text("text etrange mais particulieremnt long");
	label.active();

	return (win.run());
}
