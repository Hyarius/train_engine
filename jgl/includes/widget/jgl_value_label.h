#ifndef JGL_VALUE_LABEL_H
#define JGL_VALUE_LABEL_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_value_label : public c_widget
{
private:
	w_box_component _box;
	w_value_component _label;

public:
	c_value_label(float p_value = 0.0f, c_widget *p_parent = nullptr);
	~c_value_label();

	float value(){return (_label.value());}

	w_box_component &box(){return (_box);}
	w_value_component &label(){return (_label);}

	// - box redirection function
	void set_tileset(c_tileset *p_tileset){_box.set_tileset(p_tileset);}
	void set_back(Color p_back){_box.set_back(p_back);}
	void set_front(Color p_front){_box.set_front(p_front);}
	void set_border(int p_border){_box.set_border(p_border);}
	c_tileset *tileset(){return (_box.tileset());}
	int border(){return (_box.border());}
	Color back(){return (_box.back());}
	Color front(){return (_box.front());}

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
	void move(Vector2 delta);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif
