#include "jgl.h"

c_value_label::c_value_label(float p_value, int p_border_size,
			 Color p_back, Color p_front,
			 c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(p_border_size, p_back, p_front);
	_value = w_value_component(p_value);
	_value.set_value(p_value, _viewport->size() - _box.border_size() * 2);
}

void c_value_label::set_value(float p_value)
{
	_value.set_value(p_value, _viewport->size() - _box.border_size() * 2);
}

void c_value_label::set_format(int p_color, int p_style)
{
	_value.set_color(p_color);
	_value.set_style(p_style);
}

void c_value_label::set_border_size(int p_border_size)
{
	_box.set_border_size(p_border_size);
}

void c_value_label::set_color(Color p_back, Color p_front)
{
	_box.set_color(p_back, p_front);
}

void c_value_label::set_text_size(int p_text_size)
{
	if (p_text_size == -1)
		_value.calc_text_size(_viewport->size() - _box.border_size() * 2);
	else
		_value.set_size(p_text_size);
}

void c_value_label::set_text_color(int p_text_color)
{
	_value.set_color(p_text_color);
}

void c_value_label::set_text_style(int p_text_style)
{
	_value.set_style(p_text_style);
}

void c_value_label::set_alignment(alignment p_align)
{
	_value.set_alignment(p_align);
}

void c_value_label::set_geometry(Vector2 p_anchor, Vector2 p_size)
{
	if (_parent == nullptr)
		_viewport->resize(p_anchor, p_size);
	else
		_viewport->resize(p_anchor + _parent->anchor(), p_size);

	_value.calc_text_size(_viewport->size() - _box.border_size() * 2);
}

void c_value_label::render()
{
	_viewport->use();

	_box.render(_viewport, Vector2(0, 0), _viewport->size());

	if (_value.align() == alignment::left)
		_value.render(_viewport, _box.border_size());
	else if (_value.align() == alignment::centred)
		_value.render(_viewport, _viewport->size() / 2);
	else if (_value.align() == alignment::right)
		_value.render(_viewport, Vector2(_viewport->size().x - _box.border_size(), static_cast<float>(_box.border_size())));
}

bool c_value_label::handle_keyboard()
{
	return (false);
}

bool c_value_label::handle_mouse()
{
	return (false);
}
