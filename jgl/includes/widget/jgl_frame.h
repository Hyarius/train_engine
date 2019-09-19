#ifndef JGL_FRAME_H
#define JGL_FRAME_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_frame : public c_widget
{
private:
	w_box_component _box;


public:
	c_frame();

	~c_frame();

	void set_geometry(Vector2 p_anchor, Vector2 p_area);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif
