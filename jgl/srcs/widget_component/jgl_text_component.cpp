#include "jgl.h"

w_text_component::w_text_component(string p_text, int p_text_size, int p_text_color, int p_text_style)
{
	_text = p_text;
	_text_size = p_text_size;
	_text_color = p_text_color;
	_text_style = p_text_style;
}

void w_text_component::set_text(string p_text, Vector2 p_area)
{
	_text = p_text;

	if (p_area != -1)
		calc_text_size(p_area);
}

void w_text_component::calc_text_size(Vector2 p_area)
{
	int delta[5] = {100, 50, 20, 10, 1};
	_text_size = 2;

	if (_text == "")
		return ;

	for (int i = 0; i < 5; i++)
	{
		while (calc_text_len(_text, _text_size + delta[i]) <= p_area.x &&
			   get_char('M', _text_size + delta[i])->size().y <= p_area.y)
			_text_size += delta[i];
	}
}

void w_text_component::set_size(int p_text_size)
{
	_text_size = p_text_size;
}

void w_text_component::set_color(int p_color)
{
	_text_color = p_color;
}

void w_text_component::set_style(int p_style)
{
	_text_style = p_style;
}

void w_text_component::render(c_viewport *viewport, Vector2 pos)
{
	draw_text(viewport, _text, pos, _text_size, _text_color, _text_style);
}

void w_text_component::render_centred(c_viewport *viewport, Vector2 pos)
{
	draw_centred_text(viewport, _text, pos, _text_size, _text_color, _text_style);
}
