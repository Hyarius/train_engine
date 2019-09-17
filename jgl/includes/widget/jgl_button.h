#ifndef JGL_BUTTON_H
#define JGL_BUTTON_H

#include "jgl_text_label.h"
#include "jgl_data.h"

typedef 			void(*t_funct)(Data);

class c_button : public c_widget
{
protected:
	t_funct _funct;
	Data _param;

	w_box_component _box;
	w_text_component _text;

	int _timer;

public:
	c_button(t_funct p_funct = nullptr, Data p_param = nullptr, string p_text = "Click me", c_widget *p_parent = nullptr);

	void set_text(string p_text);
	void set_border_size(int p_border_size);
	void set_color(Color p_back, Color p_front);
	void set_text_size(int p_text_size);

	virtual void render();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
