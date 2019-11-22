#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(0.85f, 0.85f), Color(195, 195, 195));

	// c_image test = c_image(150, 150, Color(255, 0, 0, 255));
	//
	// test.active();
	//
	// draw_line(c_viewport *viewport, Color Color, Vector2 p1, Vector2 p2, int width = 1);
	//
	// int ret;
	// float play = true;
	//
	// while (play == true)
	// {
	// 	win.clear();
	//
	// 	test.draw(win.central_widget()->viewport(), Vector2(10, 10), Vector2(50, 50));
	//
	// 	win.render();
	//
	// 	ret = SDL_PollEvent(win.event());
	//
	// 	if (ret != 0)
	// 	{
	// 		if (win.event()->type == SDL_QUIT)
	// 			play = false;
	// 	}
	//
	// 	g_mouse->actualize_mouse((ret == 0 ? nullptr : win.event()));
	// }
	//
	// return (0);

	c_main_window main_window;

	return (win.run());
}
