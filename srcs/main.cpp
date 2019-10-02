#include "engine.h"

using namespace std;

void tmp(Data data)
{
	cout << "here" << endl;
}

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(860, 640), Color(195, 195, 195));

	Vector2 box_delta = Vector2(5, 5);
	Vector2 box_size = win.size() * 0.8f;

	c_frame map_box = c_frame();
	map_box.set_geometry(box_delta, box_size);
	map_box.active();

	Vector2 map_delta = map_box.box().border() * 1;
	Vector2 map_size = box_size - map_delta * 2;

	c_map map = c_map("ressources/image/map.jpg", &map_box);
	map.set_geometry(map_delta, map_size);
	map.active();

	return (win.run());
}
