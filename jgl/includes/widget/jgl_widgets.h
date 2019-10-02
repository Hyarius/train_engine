#ifndef C_WIDGETS_H
#define C_WIDGETS_H

#include "jgl_viewport.h"
#include "jgl_widget_component.h"

typedef 			void(*Funct)(Data);

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

	~c_widget();

	c_widget *parent(){return (_parent);}

	Vector2 size();

	Vector2 anchor();

	c_viewport *viewport();

	bool is_active();

	bool is_pointed(Vector2 point);

	void active();

	void set_active(bool new_state);

	void set_parent(c_widget *p_parent);

	void add_children(c_widget *p_children);

	void remove_children(c_widget *p_target);

	bool handle_event();

	void update_children();

	void render_children();

	void set_geometry(Vector2 p_anchor, Vector2 p_area);


	virtual void update(){};

	virtual void set_geometry_imp(Vector2 p_anchor, Vector2 p_area) = 0;

	virtual void render() = 0;

	virtual bool handle_keyboard() = 0;

	virtual bool handle_mouse() = 0;
};

#endif
