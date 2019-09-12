#ifndef JGL_TEXT_LABEL_H
#define JGL_TEXT_LABEL_H

#include "jgl_widgets.h"

typedef 			void(*fnct)(Data);

class c_text_label : public c_frame
{
protected:
	string _text;
	int _text_size;
	int _text_color;
	int _text_style;

public:
	c_text_label(c_widget *p_parent = nullptr, string p_text = "Click on me", int p_border_size = 3,
				 Color p_back = Color(150, 150, 150, 0), Color p_front = Color(195, 195, 195, 0));

	void set_text(string p_text);
	void set_format(int p_color = BLACK, int p_style = NORMAL);

	void set_geometry(Vector2 p_anchor, Vector2 p_size);

	void check_text_size();

	void render_text_label();

	virtual void render();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
