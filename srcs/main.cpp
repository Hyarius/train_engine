#include "engine.h"

using namespace std;

c_main_window *g_main_window;

int main(int argc, char**argv)
{
	c_application win("Train simulation engine (c)", Vector2(0.85f, 0.85f), Color(195, 195, 195));

	c_main_window main_window = c_main_window();

	g_main_window = &main_window;

	return (win.run());
}
