#ifndef JGL_TEXT_LABEL_H
#define JGL_TEXT_LABEL_H

#include "jgl_widgets.h"

typedef 			void(*fnct)(Data);

class c_text_label : public c_widget
{
protected:
	w_box_component _box;
	w_text_component _text;

public:
	c_text_label(string p_text = "Click on me", int p_border_size = 3,
				 Color p_back = Color(150, 150, 150, 0),
				 Color p_front = Color(195, 195, 195, 0),
				 c_widget *p_parent = nullptr);

	void set_text(string p_text);
	void set_format(int p_color = BLACK, int p_style = NORMAL);
	void set_border_size(int p_border_size);
	void set_color(Color p_back, Color p_front);
	void set_alignment(alignment p_align);
	void set_text_size(int p_text_size);
	void set_text_color(int p_text_color);
	void set_text_style(int p_text_style);

	void set_geometry(Vector2 p_anchor, Vector2 p_size);

	virtual void render();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
