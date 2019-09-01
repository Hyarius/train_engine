#include "jgl.h"

using namespace std;

c_widget::c_widget(c_widget *p_parent)
{
	_childrens.clear();
	set_parent(p_parent);
	_viewport = new c_viewport();
	set_background_color();
	set_geometry();
	_activated = false;
}

void c_widget::set_background_color(c_color p_background)
{
	_viewport->set_background(p_background);
}

void c_widget::set_geometry(Vector2 p_anchor, Vector2 p_size)
{
	if (_parent == NULL)
		_viewport->resize(p_anchor, p_size);
	else
		_viewport->resize(p_anchor + _parent->anchor(), p_size);
}

Vector2 c_widget::size()
{
	return (_viewport->size());
}

Vector2 c_widget::anchor()
{
	return (_viewport->anchor());
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

void c_widget::set_parent(c_widget *p_parent)
{
	_parent = p_parent;
	if (p_parent != NULL)
		p_parent->add_children(this);
}

void c_widget::add_children(c_widget *p_children)
{
	_childrens.push_back(p_children);
}

void c_widget::render()
{
	if (is_active() == false)
		return ;

	_viewport->clear();

	for (size_t i = 0; i < _childrens.size(); i++)
		_childrens[i]->render();
}

void c_widget::handle_event()
{
	if (is_active() == false)
		return ;

	handle_keyboard();
	handle_mouse();

	for (size_t i = 0; i < _childrens.size(); i++)
		_childrens[i]->handle_event();
}

void c_widget::handle_keyboard()
{

}

void c_widget::handle_mouse()
{

}
