#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(1240, 1080), Color(165, 165, 165));

	c_viewport *viewport = win->central_widget()->viewport();

	return (win.run());
}
