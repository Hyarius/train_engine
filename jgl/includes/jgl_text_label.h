#ifndef JGL_TEXT_LABEL_H
#define JGL_TEXT_LABEL_H

#include "jgl_widgets.h"

typedef 			void(*fnct)(Data);

class c_text_label : public c_frame
{
private:
	string _text;
	int _text_size;
	int _text_color;
	int _text_style;

public:
	c_text_label(c_widget *p_parent = nullptr);

	void set_text(string p_text);
	void set_format(int p_color = BLACK, int p_style = NORMAL);

	void set_geometry(Vector2 p_anchor, Vector2 p_size);

	void check_text_size();

	virtual void render();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
