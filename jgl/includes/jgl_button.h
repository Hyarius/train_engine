#ifndef JGL_BUTTON_H
#define JGL_BUTTON_H

#include "jgl_text_label.h"
#include "jgl_data.h"

typedef 			void(*t_funct)(Data);

class c_button : public c_text_label
{
protected:
	t_funct funct;
	Data param;
	int timer;

public:
	c_button(c_widget *p_parent = nullptr, t_funct p_funct = nullptr, Data p_param = nullptr);

	virtual void render();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
