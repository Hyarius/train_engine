#ifndef JGL_TAB_H
#define JGL_TAB_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_tab : public c_widget
{
private:
	vector<c_frame *> _tabs;
	vector<c_button *> _buttons;

	c_frame *tab_area;
	c_frame *button_area;

public:
	c_tab(c_widget *p_parent = nullptr);

	vector<c_frame *> tabs(){return (_tabs);}
	vector<c_button *> buttons(){return (_buttons);}

	void add_tab(string p_name, int index = -1);
	void reset_button();

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif
