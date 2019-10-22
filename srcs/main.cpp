#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(0.6f, 0.6f), Color(195, 195, 195));

	c_frame base = c_frame();
	base.set_geometry(Vector2(50, 50), Vector2(200, 200));
	base.active();

	// c_vscroll_bar bar = c_vscroll_bar(&base);
	// bar.set_geometry(0, Vector2(20, 200));
	// bar.active();

	c_button button = c_button(nullptr, nullptr, &base);
	button.set_geometry(Vector2(-20, 20), Vector2(150, 50));
	button.text().set_text("");
	button.active();

	//c_main_window main_window;

	return (win.run());
}
