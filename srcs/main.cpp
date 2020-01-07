#include "engine.h"

using namespace std;

c_main_window *main_window_ptr;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(0.85f, 0.85f), Color(195, 195, 195));

	c_main_window main_window;

	main_window_ptr = &main_window;

	return (win.run());
}
