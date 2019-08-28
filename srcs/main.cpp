#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_window win("Test", Vector2(860, 640), c_color(70, 70, 70));

	c_widget central_widget = c_widget();
	central_widget.set_geometry(Vector2(0, 0), win.size());
	central_widget.active();

	c_map map = c_map("ressources/image/map.jpg", &central_widget);
	map.set_background_color(c_color(255, 255, 255));
	map.set_geometry(Vector2(10, 10), win.size());
	map.active();

	bool play = true;
	SDL_Event event;

	while (play == true)
	{
		win.clear();

		central_widget.render();

		central_widget.handle_event();

		win.render();

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				play = false;
		}
	}

	return (0);
}
