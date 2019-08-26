#include "jgl.h"

int main(int argc, char**argv)
{
	Window win("Test", Vector2(860, 640), Color(50, 50, 50));

	bool play = true;
	SDL_Event event;

	while (play == true)
	{
		win.clear();

		win.render();

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				play = false;
		}
	}

	return (0);
}
