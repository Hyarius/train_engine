#include "jgl.h"

w_value_component::w_value_component(float p_value, int p_text_size, int p_text_color, int p_text_style, alignment p_align)
{
	_value = p_value;
	_text = ftoa(_value);
	_align = p_align;
	_text_size = p_text_size;
	_text_color = p_text_color;
	_text_style = p_text_style;
}

int w_value_component::text_size()
{
	return (_text_size);
}

void w_value_component::set_value(float p_value, Vector2 p_area)
{
	_value = p_value;
	_text = ftoa(_value);

	if (p_area != -1)
		calc_text_size(p_area);
}

void w_value_component::set_value(float p_value, int p_text_size)
{
	_value = p_value;
	_text = ftoa(_value);

	if (p_text_size != -1)
		_text_size = p_text_size;
}

void w_value_component::set_alignment(alignment p_align)
{
	_align = p_align;
}

alignment w_value_component::align()
{
	return (_align);
}

void w_value_component::calc_text_size(Vector2 p_area)
{
	int delta[5] = {100, 50, 20, 10, 1};
	_text_size = 2;
	_text = ftoa(_value);

	if (_text == "")
		return ;

	for (int i = 0; i < 5; i++)
	{
		while (calc_text_len(_text, _text_size + delta[i]) <= p_area.x &&
			   get_char('M', _text_size + delta[i])->size().y <= p_area.y)
			_text_size += delta[i];
	}
}

void w_value_component::set_size(int p_text_size)
{
	_text_size = p_text_size;
}

void w_value_component::set_color(int p_color)
{
	_text_color = p_color;
}

void w_value_component::set_style(int p_style)
{
	_text_style = p_style;
}

void w_value_component::render(c_viewport *viewport, Vector2 pos)
{
	if (_align == alignment::left)
		draw_text(viewport, _text, pos, _text_size, _text_color, _text_style);
	else if (_align == alignment::centred)
		draw_centred_text(viewport, _text, pos, _text_size, _text_color, _text_style);
	else if (_align == alignment::right)
	{
		pos.x -= calc_text_len(_text, _text_size);
		draw_text(viewport, _text, pos, _text_size, _text_color, _text_style);
	}
}
