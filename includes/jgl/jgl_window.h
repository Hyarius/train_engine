#ifndef JGL_WINDOW_H
#define JGL_WINDOW_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"

#define MOUSE_BUTTON 3
# define MOUSE_NULL -1
# define MOUSE_RIGHT 0
# define MOUSE_LEFT 1
# define MOUSE_MIDDLE 2

class c_window *main_window;

class c_mouse
{
private:
	Vector2 old_pos;
	Vector2 pos;
	Vector2 rel_pos;
	bool button[MOUSE_BUTTON];

public:
	c_mouse()
	{
		old_pos = Vector2(-1, -1);
		pos = Vector2(-1, -1);
		rel_pos = Vector2(0, 0);
		button[MOUSE_LEFT] = false;
		button[MOUSE_RIGHT] = false;
		button[MOUSE_MIDDLE] = false;
	}
	void		actualize_mouse()
	{
		int x, y;
		Uint32 mousestate;

		old_pos = pos;
		mousestate = SDL_GetMouseState(&(x), &(y));
		pos = Vector2(x, y);
		if (old_pos.x != -1)
			rel_pos = pos - old_pos;
		if (mousestate & SDL_BUTTON(SDL_BUTTON_LEFT))
			button[MOUSE_LEFT] = true;
		else
			button[MOUSE_LEFT] = false;
		if (mousestate & SDL_BUTTON(SDL_BUTTON_RIGHT))
			button[MOUSE_RIGHT] = true;
		else
			button[MOUSE_RIGHT] = false;
		if (mousestate & SDL_BUTTON(SDL_BUTTON_MIDDLE))
			button[MOUSE_MIDDLE] = true;
		else
			button[MOUSE_MIDDLE] = false;
	}
	int			get_button(int type)
	{
		if (type < MOUSE_RIGHT || type > MOUSE_MIDDLE)
			return (-1);
		return (button[type]);
	}

};

class c_keyboard
{
private:
	char clicked;
	const Uint8	*state;

public:
	c_keyboard() { state = SDL_GetKeyboardState(NULL); }
	int			get_key(int scan_code) { return ((state[scan_code] != 0 ? 1 : 0)); }
	void		reset_key(int scan_code) { ((Uint8	*)state)[scan_code] = 0; }
};

class c_window
{
private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;
	c_color _background;
	Vector2 _win_size;

	c_keyboard _keyboard;
	c_mouse _mouse;

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

		_mouse = c_mouse();
		_keyboard = c_keyboard();

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

	int	get_key(int scan_code) { return (_keyboard.get_key(scan_code)); }
	void reset_key(int scan_code) { _keyboard.reset_key(scan_code); }
	void actualize_mouse(){_mouse.actualize_mouse();}
	int	get_button(int type){return (_mouse.get_button(type));}
};

#endif
