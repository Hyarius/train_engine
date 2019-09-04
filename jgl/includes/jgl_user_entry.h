#ifndef JGL_USER_ENTRY_H
#define JGL_USER_ENTRY_H

#include "jgl_widgets.h"

class c_user_entry : public c_frame
{
private:
	string text;

public:
	c_user_entry(c_widget *p_parent = NULL);

	virtual void render();

	virtual void handle_keyboard();

	virtual void handle_mouse();
};

#endif
