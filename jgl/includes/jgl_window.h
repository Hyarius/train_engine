#ifndef C_WINDOW_H
#define C_WINDOW_H

#include "jgl_widgets.h"

using namespace std;

class c_window : public c_widget
{
protected:
	c_color back;

public:
	c_window(c_widget *p_parent = NULL,
			c_color p_back = c_color(220, 220, 220));

	virtual void render();

	virtual void handle_keyboard();

	virtual void handle_mouse();
};

#endif
