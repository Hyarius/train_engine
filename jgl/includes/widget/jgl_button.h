#ifndef JGL_BUTTON_H
#define JGL_BUTTON_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_button : public c_widget
{
private:
	w_box_component _box;
	w_text_component _text;

	Funct _funct;
	Color _delta;
	Data _data;
	int _timer;

public:
	c_button(Funct p_funct = nullptr, Data p_data = nullptr, c_widget *p_parent = nullptr);
	~c_button();


	w_box_component &box(){return (_box);}
	w_text_component &text(){return (_text);}

	void set_funct(Funct p_funct, Data p_data)
	{
		_funct = p_funct;
		_data = p_data;
	}

	void set_delta(Color p_delta){_delta = p_delta;}

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif
