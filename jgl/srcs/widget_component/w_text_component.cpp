#include "jgl.h"

w_text_component::w_text_component(string p_text, Vector2 p_anchor, Vector2 p_area, int p_size, alignment p_align, text_color p_color, text_style p_style)
{
	_text = p_text;
	_anchor = p_anchor;
	_area = p_area;
	_align = p_align;
	_size = p_size;
	_color = p_color;
	_style = p_style;
}

w_text_component::~w_text_component()
{

}

void w_text_component::calc_text_size()
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

void w_text_component::render(c_viewport *viewport)
{

}
