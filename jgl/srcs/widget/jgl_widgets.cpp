#include "jgl.h"

using namespace std;

c_widget::c_widget(c_widget *p_parent)
{
	_childrens.clear();
	set_parent(p_parent);
	_viewport = new c_viewport();
	_activated = false;
}

Vector2 c_widget::size()
{
	return (_viewport->size());
}

Vector2 c_widget::anchor()
{
	return (_viewport->anchor());
}

void c_widget::set_geometry(Vector2 p_anchor, Vector2 p_area)
{
	if (_parent == nullptr)
		_viewport->resize(p_anchor, p_area);
	else
		_viewport->resize(p_anchor + _parent->anchor(), p_area);

	set_geometry_imp(p_anchor, p_area);
}

c_viewport *c_widget::viewport()
{
	return (_viewport);
}

bool c_widget::is_active()
{
	return (_activated);
}

void c_widget::active()
{
	_activated = !_activated;
}

void c_widget::set_active(bool new_state)
{
	_activated = new_state;
}

void c_widget::set_parent(c_widget *p_parent)
{
	if (p_parent != nullptr)
		_parent = p_parent;
	else
		_parent = g_application->central_widget();

	if (_parent != nullptr)
		_parent->add_children(this);
}

void c_widget::add_children(c_widget *p_children)
{
	_childrens.push_back(p_children);
}

bool c_widget::handle_event()
{
	if (is_active() == false)
		return (false);

	for (int i = _childrens.size() - 1; i >= 0; i--)
		if (_childrens[i]->handle_event() == true)
			return (true);

	bool key = handle_keyboard();
	bool mouse = handle_mouse();

	if (key == true || mouse == true)
		return (true);
	return (false);
}

bool c_widget::is_pointed(Vector2 point)
{
	Vector2 pos1, pos2;

	pos1 = _viewport->anchor() + _parent->anchor();
	pos2 = pos1 + _viewport->size();
	if (point.x < pos1.x || point.x > pos2.x || point.y < pos1.y || point.y > pos2.y)
		return (false);
	return (true);
}

void c_widget::render_children()
{
	if (is_active() == false)
		return ;

	_viewport->use();
	render();

	for (size_t i = 0; i < _childrens.size(); i++)
	{
		_childrens[i]->render_children();
	}
}

void c_widget::update_children()
{
	if (is_active() == false)
		return ;

	update();

	for (size_t i = 0; i < _childrens.size(); i++)
	{
		_childrens[i]->update_children();
	}
}
