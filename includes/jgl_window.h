#ifndef JGL_WINDOW_H
#define JGL_WINDOW_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"

class c_window *main_window;

class c_window
{
private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;
	c_color _background;
	Vector2 _win_size;

public:
	c_window(string name, Vector2 p_size = Vector2(), c_color p_color = c_color(50, 50, 50))
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

		if (main_window == nullptr)
			select();
	}

	SDL_Window *window()
	{
		return (_window);
	}

	SDL_Renderer *renderer()
	{
		return (_renderer);
	}

	void set_background(c_color p_color = c_color(50, 50, 50))
	{
		_background = p_color;
	}

	Vector2 size()
	{
		return (_win_size);
	}

	void select()
	{
		main_window = this;
	}

	void clear()
	{
		SDL_SetRenderDrawColor(_renderer, _background.r * 255, _background.g * 255, _background.b * 255, _background.a * 255);
		SDL_RenderClear(_renderer);
	}

	void render()
	{
		SDL_RenderPresent(_renderer);
	}
};

#endif
