#include "jgl.h"

c_application *main_window;

c_application::c_application(string name, Vector2 p_size, c_color p_color)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	_win_size = p_size;
	if (_win_size == Vector2())
	{
		SDL_DisplayMode current;
		SDL_GetDesktopDisplayMode(0, &current);
		_win_size = Vector2(current.w * 0.8f, current.h * 0.8f);
	}

	_window = SDL_CreateWindow(name.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		static_cast<int>(_win_size.x), static_cast<int>(_win_size.y), 0);

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

	_background = p_color;

	mouse = new t_mouse();
	keyboard = new t_keyboard();

	if (main_window == nullptr)
		select();

	_central_widget = new c_window();
	_central_widget->set_geometry(Vector2(0, 0), _win_size);
	_central_widget->active();
}

SDL_Window *c_application::window()
{
	return (_window);
}

SDL_Renderer *c_application::renderer()
{
	return (_renderer);
}

c_widget *c_application::central_widget()
{
	return (_central_widget);
}

void c_application::set_background(c_color p_color)
{
	_background = p_color;
}

Vector2 c_application::size()
{
	return (_win_size);
}

void c_application::select()
{
	main_window = this;
}

void c_application::clear()
{
	SDL_SetRenderDrawColor(_renderer, _background.r * 255, _background.g * 255, _background.b * 255, _background.a * 255);
	SDL_RenderClear(_renderer);
}

void c_application::render()
{
	SDL_RenderPresent(_renderer);
}

int c_application::run()
{
	play = true;

	while (play == true)
	{
		clear();

		_central_widget->render();

		_central_widget->handle_event();

		render();

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				play = false;
			mouse->actualize_mouse(&event);
		}
		else
			mouse->actualize_mouse();
	}

	return (0);
}
