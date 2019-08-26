#include "jgl.h"

using namespace std;

int main(int argc, char**argv)
{
	c_window win("Test", Vector2(860, 640), c_color(70, 70, 70));

	c_viewport *port = new c_viewport(c_color(110, 110, 110), Vector2(50, 50), Vector2(350, 350));
	c_viewport *port2 = new c_viewport(c_color(150, 150, 150), Vector2(400, 400), Vector2(100, 100));

	bool play = true;
	SDL_Event event;

	c_image image("ressources/image/zoro.png");

	while (play == true)
	{
		win.clear();
		port->clear();
		port2->clear();

		draw_text(port, "ceci est une string de text plutot longue, et qui devrait donc deborder", Vector2(10, 10), 30, DARK_RED);

		win.render();

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				play = false;
		}
	}

	return (0);
}
