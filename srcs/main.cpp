#include "engine.h"

using namespace std;

void tmp(Data data)
{
	cout << "here" << endl;
}

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(1240, 1080), Color(15, 15, 15));

	c_user_entry label = c_user_entry();
	label.set_geometry(Vector2(150, 150), Vector2(500, 50));
	label.entry().set_align(alignment::right);
	label.active();

	return (win.run());
}
