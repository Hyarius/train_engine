#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(0.8f, 0.8f), Color(195, 195, 195));

	c_tab tab = c_tab();

	tab.set_geometry(Vector2(50, 50), Vector2(500, 650));

	tab.active();

	

	// c_main_window main_window;

	// c_frame map_box;
	// c_frame train_box;
	// c_frame command_box;
	// c_frame config_box;
	// c_frame travel_box;
	//
	// vector<c_frame *>frames;
	//
	// frames = {&map_box, &train_box, &command_box, &config_box, &travel_box};
	//
	// create_box(&win, frames);
	//
	// Vector2 map_delta = map_box.box().border() * 1;
	// Vector2 map_size = map_box.box().area() - map_delta * 2;
	//
	// c_map map = c_map("ressources/image/map.jpg", &map_box);
	// map.set_geometry(map_delta, map_size);
	// map.active();

	return (win.run());
}
