#include "jgl.h"

w_value_component::w_value_component(float p_value)
{
	_value = p_value;
	_text = ftoa(_value);
	_anchor = Vector2();
	_area = Vector2();
	_align = alignment::left;
	_size = 16;
	_color = text_color::black;
	_style = text_style::normal;
}

w_value_component::~w_value_component()
{

}

void 		w_value_component::calc_text_size()
{
	int delta[5] = {100, 50, 20, 10, 1};
	_size = 2;
	_text = ftoa(_value);

	if (_text == "")
		return ;

	for (int i = 0; i < 5; i++)
	{
		while (calc_text_len(_text, _size + delta[i]) <= _area.x &&
			   get_char('M', _size + delta[i])->size().y <= _area.y)
			_size += delta[i];
	}
}

void w_value_component::render(c_viewport *viewport)
{
	Vector2 pos;

	if (_align == alignment::left)
	{
		pos.x = calc_text_len(_text, _size) / 2.0f;
		pos.y = _area.y / 2.0f;
	}
	else if (_align == alignment::centred)
	{
		pos = _area / 2;
	}
	else if (_align == alignment::right)
	{
		pos.x = _area.x - calc_text_len(_text, _size) / 2.0f;
		pos.y = _area.y / 2.0f;
	}
	draw_centred_text(viewport, _text, pos + _anchor - viewport->anchor(), _size, _color, _style);
}
