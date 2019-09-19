#ifndef JGL_TEXT_LABEL_H
#define JGL_TEXT_LABEL_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_text_label : public c_widget
{
private:

public:

	void set_geometry(Vector2 p_anchor, Vector2 p_area){}

	void render(){}

	bool handle_mouse(){return (false);}

	bool handle_keyboard(){return (false);}
};

#endif
