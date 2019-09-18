#ifndef JGL_VALUE_LABEL_H
#define JGL_VALUE_LABEL_H

#include "jgl_widgets.h"

class c_value_label : public c_widget
{
protected:
	w_box_component _box;
	w_value_component _value;

public:
	c_value_label(float p_value = 0.0f, int p_border_size = 3,
				 Color p_back = Color(150, 150, 150, 0),
				 Color p_front = Color(195, 195, 195, 0),
				 c_widget *p_parent = nullptr);

	void set_value(float p_value);
	void set_format(int p_color = BLACK, int p_style = NORMAL);
	void set_border_size(int p_border_size);
	void set_color(Color p_back, Color p_front);
	void set_text_size(int p_text_size);
	void set_text_color(int p_text_color);
	void set_text_style(int p_text_style);
	void set_alignment(alignment p_align);

	void set_geometry(Vector2 p_anchor, Vector2 p_size);

	virtual void render();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
