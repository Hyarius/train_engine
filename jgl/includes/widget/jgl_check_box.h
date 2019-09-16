#ifndef JGL_CHECK_BOX_H
#define JGL_CHECK_BOX_H

#include "jgl_widgets.h"

class c_check_box : public c_widget
{
protected:
	bool checked;

public:
	c_check_box(c_widget *p_parent = nullptr);

	void check_text_size();

	void render_check_box();

	virtual void render();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
