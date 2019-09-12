#ifndef JGL_USER_ENTRY_H
#define JGL_USER_ENTRY_H

#include "jgl_frame.h"

class c_user_entry : public c_frame
{
protected:
	bool selected;
	string text;
	int cursor;

	Uint32 next_input;
	Uint32 input_delay;

public:
	c_user_entry(c_widget *p_parent = nullptr);

	void select();
	void unselect();

	virtual void render();
	void render_text();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
