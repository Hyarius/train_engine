#ifndef JGL_USER_ENTRY_H
#define JGL_USER_ENTRY_H

#include "jgl_frame.h"

class c_user_entry : public c_widget
{
protected:
	w_box_component _box;
	w_entry_component _entry;

	Uint32 next_input;
	Uint32 input_delay;

public:
	c_user_entry(int p_border_size = 3,
				 Color p_back = Color(150, 150, 150),
				 Color p_front = Color(195, 195, 195),
				 c_widget *p_parent = nullptr);

	virtual void render();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
