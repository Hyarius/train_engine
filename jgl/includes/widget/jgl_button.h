#ifndef JGL_BUTTON_H
#define JGL_BUTTON_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_button : public c_widget
{
private:
	w_box_component _box;
	w_text_component _text;

public:
	c_button(c_widget *p_parent = nullptr);
	~c_button();

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area){}

	void render(){}

	bool handle_mouse(){return (false);}

	bool handle_keyboard(){return (false);}
};

#endif
