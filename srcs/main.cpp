#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(0.6f, 0.6f), Color(195, 195, 195));

	c_main_window main_window; 

	return (win.run());
}
