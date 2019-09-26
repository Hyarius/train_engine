#include "jgl.h"

w_textual_component::w_textual_component(c_widget *p_owner) : w_component(p_owner)
{
	_text = "";
	_align = alignment::left;
	_size = 16;
	_color = text_color::black;
	_style = text_style::normal;
}

void 		w_textual_component::calc_text_size()
{
	int delta[5] = {100, 50, 20, 10, 1};
	_size = 2;

	if (_text == "")
		return ;

	for (int i = 0; i < 5; i++)
	{
		while (calc_text_len(_text, _size + delta[i]) <= _area.x &&
			   get_char('M', _size + delta[i])->size().y <= _area.y)
			_size += delta[i];
	}
}

void 		w_textual_component::calc_text_size_height()
{
	int delta[5] = {100, 50, 20, 10, 1};
	_size = 2;

	for (int i = 0; i < 5; i++)
	{
		while (get_char('M', _size + delta[i])->size().y <= _area.y)
			_size += delta[i];
	}
}
