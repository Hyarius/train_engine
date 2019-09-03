#include "jgl.h"

c_window *main_window;

c_window::c_window(string name, Vector2 p_size, c_color p_color)
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

	_background = p_color;

	mouse = new t_mouse();
	keyboard = new t_keyboard();

	if (main_window == nullptr)
		select();
}

SDL_Window *c_window::window()
{
	return (_window);
}

SDL_Renderer *c_window::renderer()
{
	return (_renderer);
}

void c_window::set_background(c_color p_color)
{
	_background = p_color;
}

Vector2 c_window::size()
{
	return (_win_size);
}

void c_window::select()
{
	main_window = this;
}

void c_window::clear()
{
	SDL_SetRenderDrawColor(_renderer, _background.r * 255, _background.g * 255, _background.b * 255, _background.a * 255);
	SDL_RenderClear(_renderer);
}

void c_window::render()
{
	SDL_RenderPresent(_renderer);
}
