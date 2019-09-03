#ifndef C_FRAME_H
#define C_FRAME_H

#include "jgl_widgets.h"

using namespace std;

class c_frame : public c_widget
{
protected:
	int border_size;
	c_color front;
	c_color back;

public:
	c_frame(c_widget *p_parent = NULL, int p_border_size = 0,
			c_color p_front = c_color(120, 120, 120),
			c_color p_back = c_color(165, 165, 165));

	virtual void render();

	virtual void handle_keyboard();

	virtual void handle_mouse();
};

#endif
