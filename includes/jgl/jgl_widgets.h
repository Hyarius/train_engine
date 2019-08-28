#ifndef c_widgetS_H
#define c_widgetS_H

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
	c_widget(c_widget *p_parent = NULL)
	{
		_childrens.clear();
		set_parent(p_parent);
		_viewport = new c_viewport();
		set_background_color();
		set_geometry();
		_activated = false;
	}

	void set_background_color(c_color p_background = c_color(50, 50, 50))
	{
		_viewport->set_background(p_background);
	}

	void set_geometry(Vector2 p_anchor = Vector2(0, 0), Vector2 p_size = Vector2(0, 0))
	{
		if (_parent == NULL)
			_viewport->resize(p_anchor, p_size);
		else
			_viewport->resize(p_anchor + _parent->anchor(), p_size);
	}

	Vector2 size()
	{
		return (_viewport->size());
	}

	Vector2 anchor()
	{
		return (_viewport->anchor());
	}

	c_viewport *viewport()
	{
		return (_viewport);
	}

	bool is_active()
	{
		return (_activated);
	}

	void active()
	{
		_activated = !_activated;
	}

	void set_parent(c_widget *p_parent)
	{
		_parent = p_parent;
		if (p_parent != NULL)
			p_parent->add_children(this);
	}

	void add_children(c_widget *p_children)
	{
		_childrens.push_back(p_children);
	}

	virtual void render()
	{
		if (is_active() == false)
			return ;

		_viewport->clear();

		for (size_t i = 0; i < _childrens.size(); i++)
			_childrens[i]->render();
	}

	void handle_event()
	{
		if (is_active() == false)
			return ;

		handle_keyboard();
		handle_mouse();

		for (size_t i = 0; i < _childrens.size(); i++)
			_childrens[i]->handle_event();
	}

	virtual void handle_keyboard()
	{

	}

	virtual void handle_mouse()
	{

	}
};

#endif
