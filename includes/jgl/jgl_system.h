#ifndef JGL_SYSTEM_H
#define JGL_SYSTEM_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"

#define MOUSE_BUTTON 3
# define MOUSE_NULL -1
# define MOUSE_RIGHT 0
# define MOUSE_LEFT 1
# define MOUSE_MIDDLE 2

typedef struct s_mouse
{
	Vector2 old_pos;
	Vector2 pos;
	Vector2 rel_pos;
	float wheel;
	bool button[MOUSE_BUTTON];

	s_mouse();
	void actualize_mouse(SDL_Event *event = NULL);
	int get_button(int type);

}t_mouse;

typedef struct s_keyboard
{
	char clicked;
	const Uint8	*state;

	s_keyboard();
	int get_key(int scan_code);
	void reset_key(int scan_code);
}t_keyboard;

class c_window
{
private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;
	c_color _background;
	Vector2 _win_size;


public:
	c_window(string name, Vector2 p_size = Vector2(), c_color p_color = c_color(50, 50, 50));

	SDL_Window *window();

	SDL_Renderer *renderer();

	void set_background(c_color p_color = c_color(50, 50, 50));

	Vector2 size();

	void select();

	void clear();

	void render();
};

#endif
