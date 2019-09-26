#include "engine.h"

using namespace std;

void tmp(Data data)
{
	cout << "here" << endl;
}

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(1240, 1080), Color(195, 195, 195));

	c_frame map_box = c_frame();
	map_box.set_geometry(Vector2(5, 5), Vector2(1050, 850));
	map_box.box().set_front(Color(0, 0, 0));
	map_box.box().set_back(Color(255, 255, 255));
	map_box.active();

	// c_map map = c_map("ressources/image/map.jpg", &map_box);
	// map.set_geometry(Vector2(3, 3), Vector2(1044, 844));
	// map.active();

	// c_frame map_box2 = c_frame();
	// map_box2.set_geometry(Vector2(23, 0), Vector2(100, 23));
	// map_box2.box().set_front(Color(255, 0, 0));
	// map_box2.box().set_back(Color(0, 0, 255));
	// map_box2.active();

	c_frame map_box3 = c_frame(&map_box);
	map_box3.set_geometry(Vector2(18, 18), Vector2(100, 100));
	map_box3.box().set_front(Color(0, 150, 0));
	map_box3.box().set_back(Color(0, 255, 0));
	map_box3.active();

	return (win.run());
}
