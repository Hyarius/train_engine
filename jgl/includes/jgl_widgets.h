#ifndef C_WIDGETS_H
#define C_WIDGETS_H

#include "jgl_viewport.h"

using namespace std;

class c_widget
{
protected:
	c_widget *_parent;
	vector<c_widget *> _childrens;
	c_viewport *_viewport;
	bool _activated;

public:
	c_widget(c_widget *p_parent = NULL);

	void set_background_color(c_color p_background = c_color(50, 50, 50));

	void set_geometry(Vector2 p_anchor = Vector2(0, 0), Vector2 p_size = Vector2(0, 0));

	Vector2 size();

	Vector2 anchor();

	c_viewport *viewport();

	bool is_active();

	void active();

	void set_parent(c_widget *p_parent);

	void add_children(c_widget *p_children);

	virtual void render();

	void handle_event();

	virtual void handle_keyboard();

	virtual void handle_mouse();
};

#endif
