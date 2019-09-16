#ifndef C_WIDGETS_H
#define C_WIDGETS_H

#include "jgl_viewport.h"
#include "jgl_widget_component.h"

using namespace std;

class c_widget
{
protected:
	c_widget *_parent;
	vector<c_widget *> _childrens;
	c_viewport *_viewport;
	bool _activated;

public:
	c_widget(c_widget *p_parent = nullptr);

	void set_geometry(Vector2 p_anchor, Vector2 p_size);

	Vector2 size();

	Vector2 anchor();

	c_viewport *viewport();

	bool is_active();

	bool is_pointed(Vector2 point);

	void active();

	void set_parent(c_widget *p_parent);

	void add_children(c_widget *p_children);


	bool handle_event();

	void render_children();



	virtual void render() = 0;

	virtual bool handle_keyboard() = 0;

	virtual bool handle_mouse() = 0;
};

#endif
