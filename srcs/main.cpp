#include "jgl.h"

using namespace std;

int main(int argc, char**argv)
{
	c_window win("Test", Vector2(860, 640), c_color(70, 70, 70));

	bool play = true;
	SDL_Event event;

	jgl_widget widget = jgl_widget();
	widget.set_geometry(Vector2(20, 20), Vector2(300, 300));

	jgl_widget widget2 = jgl_widget(&widget);
	widget2.set_background_color(c_color(150, 150, 150));
	widget2.set_geometry(Vector2(10, 10), Vector2(100, 100));

	jgl_widget widget3 = jgl_widget(&widget2);
	widget3.set_background_color(c_color(200, 200, 200));
	widget3.set_geometry(Vector2(-10, -10), Vector2(100, 50));

	while (play == true)
	{
		win.clear();

		widget.render();

		win.render();

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				play = false;
		}
	}

	return (0);
}
