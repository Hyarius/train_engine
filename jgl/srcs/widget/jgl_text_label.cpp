#include "jgl.h"

c_text_label::c_text_label(string p_text, int p_border_size,
			 Color p_back, Color p_front,
			 c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(p_border_size, p_back, p_front);
	_text = w_text_component(p_text);
	_text.set_alignment(alignment::left);
	_text.set_text(p_text, _viewport->size() - _box.border_size() * 2);
}

void c_text_label::set_text(string p_text)
{
	_text.set_text(p_text, _viewport->size() - _box.border_size() * 2);
}

void c_text_label::set_format(int p_color, int p_style)
{
	_text.set_color(p_color);
	_text.set_style(p_style);
}

void c_text_label::set_border_size(int p_border_size)
{
	_box.set_border_size(p_border_size);
}

void c_text_label::set_color(Color p_back, Color p_front)
{
	_box.set_color(p_back, p_front);
}

void c_text_label::set_text_size(int p_text_size)
{
	if (p_text_size == -1)
		_text.calc_text_size(_viewport->size() - _box.border_size() * 2);
	else
		_text.set_size(p_text_size);
}

void c_text_label::set_text_color(int p_text_color)
{
	_text.set_color(p_text_color);
}

void c_text_label::set_text_style(int p_text_style)
{
	_text.set_style(p_text_style);
}

void c_text_label::set_alignment(alignment p_align)
{
	_text.set_alignment(p_align);
}

void c_text_label::set_geometry(Vector2 p_anchor, Vector2 p_size)
{
	if (_parent == nullptr)
		_viewport->resize(p_anchor, p_size);
	else
		_viewport->resize(p_anchor + _parent->anchor(), p_size);

	_text.calc_text_size(_viewport->size() - _box.border_size() * 2);
}

void c_text_label::render()
{
	_viewport->use();

	_box.render(_viewport, Vector2(0, 0), _viewport->size());

	if (_text.align() == alignment::left)
		_text.render(_viewport, _box.border_size());
	else if (_text.align() == alignment::centred)
		_text.render(_viewport, _viewport->size() / 2);
	else if (_text.align() == alignment::right)
		_text.render(_viewport, Vector2(_viewport->size().x - _box.border_size(), static_cast<float>(_box.border_size())));
}

bool c_text_label::handle_keyboard()
{
	return (false);
}

bool c_text_label::handle_mouse()
{
	return (false);
}
