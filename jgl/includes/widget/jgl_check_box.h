#ifndef JGL_CHECK_BOX_H
#define JGL_CHECK_BOX_H

#include "jgl_widgets.h"

class c_check_box : public c_widget
{
protected:
	w_box_component _box;
	w_text_component _text;
	w_check_component _check;

public:
	c_check_box(c_widget *p_parent = nullptr);

	void set_text(string new_text, int p_text_size = -1);

	virtual void render();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
