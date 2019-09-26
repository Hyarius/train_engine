#include "engine.h"

using namespace std;

void tmp(Data data)
{
	cout << "here" << endl;
}

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(1240, 1080), Color(15, 15, 15));

	c_map map = c_map("ressources/image/map.jpg");
	map.set_geometry(Vector2(50, 50), Vector2(1050, 850));
	map.active();

	return (win.run());
}
