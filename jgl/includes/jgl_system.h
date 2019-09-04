#ifndef JGL_SYSTEM_H
#define JGL_SYSTEM_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"

#define MOUSE_DOWN 1
#define MOUSE_UP 0
#define MOUSE_NULL -1

#define MOUSE_BUTTON 3

# define MOUSE_RIGHT 0
# define MOUSE_LEFT 1
# define MOUSE_MIDDLE 2

typedef struct s_mouse
{
	Vector2 old_pos;
	Vector2 pos;
	Vector2 rel_pos;
	float wheel;
	int button[MOUSE_BUTTON];
	bool motion;

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

#endif
