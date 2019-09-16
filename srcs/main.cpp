#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(1240, 1080), Color(15, 15, 15));

	c_user_entry label = c_user_entry();
	label.set_geometry(Vector2(50, 50), Vector2(150, 50));
	//label.set_text("text etrange");
	label.active();

	return (win.run());
}
