#include "jgl.h"

c_check_box::c_check_box(c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component();
	_text = w_text_component("Checkbox");
	_check = w_check_component();}

void c_check_box::render()
{
	Vector2 pos = Vector2(_viewport->size().y,_viewport->size().y / 2.0f - _text.text_size() / 2.0f);
	_viewport->use();

	_box.render(_viewport, 0, _viewport->size());
	_text.render(_viewport, pos);
	_check.render(_viewport, 4, _viewport->size().y - 8);
}

void c_check_box::set_text(string new_text, int p_text_size)
{
	if (p_text_size == -1)
		_text.set_text(new_text, _viewport->size() - Vector2(_viewport->size().y, 0.0f) - 4);
	else
		_text.set_text(new_text, p_text_size);
}

bool c_check_box::handle_keyboard()
{
	return (false);
}

bool c_check_box::handle_mouse()
{
	if (g_mouse->get_button(MOUSE_LEFT) == MOUSE_UP &&
		_check.check(g_mouse->pos,
					_viewport->anchor() + 4,
					_viewport->anchor() + _viewport->size().y - 8))
	{
		_check.set_state(!_check.state());
	}

	return (false);
}
