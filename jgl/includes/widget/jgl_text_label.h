#ifndef JGL_TEXT_LABEL_H
#define JGL_TEXT_LABEL_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_text_label : public c_widget
{
private:
	w_box_component _box;
	w_text_component _text;

public:
	c_text_label(string p_text = "", c_widget *p_parent = nullptr);
	~c_text_label();

	w_box_component &box(){return (_box);}
	w_text_component &text(){return (_text);}


	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif
