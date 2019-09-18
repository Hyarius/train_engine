#include "jgl.h"

c_button::c_button(string p_text, t_funct p_funct, Data p_param, c_widget *p_parent) : c_widget(p_parent)
{
	_funct = p_funct;
	_param = p_param;
	_box = w_box_component();
	_text = w_text_component();
	_text.set_text(p_text, _viewport->size() - _box.border_size() * 2);
	_text.set_alignment(alignment::centred);
	_timer = 0;
}

void c_button::set_text(string p_text)
{
	_text.set_text(p_text, _viewport->size() - _box.border_size() * 2);
}

void c_button::set_text_size(int p_text_size)
{
	if (p_text_size == -1)
		_text.calc_text_size(_viewport->size() - _box.border_size() * 2);
	else
		_text.set_size(p_text_size);
}

void c_button::set_text_color(int p_text_color)
{
	_text.set_color(p_text_color);
}

void c_button::set_text_style(int p_text_style)
{
	_text.set_style(p_text_style);
}

void c_button::set_border_size(int p_border_size)
{
	_box.set_border_size(p_border_size);
}

void c_button::set_color(Color p_back, Color p_front)
{
	_box.set_color(p_back, p_front);
}

void c_button::set_alignment(alignment p_align)
{
	_text.set_alignment(p_align);
}

void c_button::set_geometry(Vector2 p_anchor, Vector2 p_size)
{
	if (_parent == nullptr)
		_viewport->resize(p_anchor, p_size);
	else
		_viewport->resize(p_anchor + _parent->anchor(), p_size);

	_text.calc_text_size(_viewport->size() - _box.border_size() * 2);
}

void c_button::set_funct(t_funct p_funct, Data p_param)
{
	_funct = p_funct;
	_param = p_param;
}

void c_button::render()
{
	_viewport->use();

	if (_timer > 0 && _timer--)
		_box.render(_viewport, 0, _viewport->size(), Color(50, 50, 50, 150));
	else
		_box.render(_viewport, 0, _viewport->size());

	if (_text.align() == alignment::left)
		_text.render(_viewport, _box.border_size());
	else if (_text.align() == alignment::centred)
		_text.render(_viewport, _viewport->size() / 2);
	else if (_text.align() == alignment::right)
		_text.render(_viewport, Vector2(_viewport->size().x - _box.border_size(), static_cast<float>(_box.border_size())));
}

bool c_button::handle_keyboard()
{
	return (false);
}

bool c_button::handle_mouse()
{
	if (g_mouse->get_button(MOUSE_LEFT) == MOUSE_DOWN && is_pointed(g_mouse->pos))
		_timer = 12;

	if (_timer == 0 && g_mouse->get_button(MOUSE_LEFT) == MOUSE_UP && is_pointed(g_mouse->pos))
	{
		if (_funct != nullptr)
			_funct(_param);
	}

	return (false);
}
