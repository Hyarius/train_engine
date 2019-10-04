#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(0.8f, 0.8f), Color(195, 195, 195));

	/*
	c_tab tab = c_tab();

	tab.add_tab("Tab 1");
	tab.add_tab("Pas Tab 1");
	tab.add_tab("Tab 3");

	tab.set_geometry(Vector2(50, 50), Vector2(500, 650));

	tab.active();
	*/

	c_main_window main_window;

	return (win.run());
}
