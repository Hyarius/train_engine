#ifndef JGL_USER_ENTRY
#define JGL_USER_ENTRY

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_user_entry : public c_widget
{
private:
	w_box_component _box;
	w_entry_component _entry;

	bool _select;
	Uint32 _next_input;
	Uint32 _input_delay;

public:
	c_user_entry(c_widget *p_parent = nullptr);
	~c_user_entry();

	w_box_component &box(){return (_box);}
	w_entry_component &entry(){return (_entry);}

	void select(){_select = true;}
	void unselect(){_select = false;}
	bool selected(){return (_select);}

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);

	void render();

	bool handle_mouse();

	bool handle_keyboard();
};

#endif
