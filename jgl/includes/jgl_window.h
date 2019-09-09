#ifndef C_WINDOW_H
#define C_WINDOW_H

#include "jgl_widgets.h"

using namespace std;

class c_window : public c_widget
{
protected:
	Color back;

public:
	c_window(c_widget *p_parent = NULL,
			Color p_back = Color(220, 220, 220));

	virtual void render();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
