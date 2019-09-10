#ifndef C_FRAME_H
#define C_FRAME_H

#include "jgl_widgets.h"

using namespace std;

class c_frame : public c_widget
{
protected:
	int border_size;
	Color front;
	Color back;

public:
	c_frame(c_widget *p_parent = NULL, int p_border_size = 0,
			Color p_front = Color(120, 120, 120),
			Color p_back = Color(165, 165, 165));

	void set_color(
		Color p_front = Color(120, 120, 120),
		Color p_back = Color(165, 165, 165));

	void set_border_size(int p_border_size = 0);

	void render_frame();

	virtual void render();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
