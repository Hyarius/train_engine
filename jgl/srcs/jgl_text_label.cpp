#include "jgl.h"

c_text_label::c_text_label(c_widget *p_parent) : c_frame(p_parent, 3, Color(255, 165, 165, 0), Color(255, 185, 185, 0))
{
	_text = "";
	_text_size = 2;
	_text_color = BLACK;
	_text_style = NORMAL;
}

void c_text_label::set_text(string p_text)
{
	_text = p_text;
	check_text_size();
}

void c_text_label::set_format(int p_color, int p_style)
{
	_text_color = p_color;
	_text_style = p_style;
}

void c_text_label::check_text_size()
{
	int inside_size = _viewport->size().x - border_size * 6;
	int inside_height = _viewport->size().y - border_size * 2;
	int delta[5] = {100, 50, 20, 10, 1};
	_text_size = 2;

	if (_text == "")
		return ;

	for (int i = 0; i < 5; i++)
	{
		while (calc_text_len(_text, _text_size + delta[i]) <= inside_size &&
			   get_char('M', _text_size + delta[i])->size().y <= inside_height)
			_text_size += delta[i];
	}
}

void c_text_label::set_geometry(Vector2 p_anchor, Vector2 p_size)
{
	if (_parent == nullptr)
		_viewport->resize(p_anchor, p_size);
	else
		_viewport->resize(p_anchor + _parent->anchor(), p_size);

	check_text_size();
}

void c_text_label::render()
{
	_viewport->use();

	render_frame();

	draw_centred_text(_viewport, _text, _viewport->size() / 2, _text_size, _text_color, _text_style);
}

bool c_text_label::handle_keyboard()
{
	return (false);
}

bool c_text_label::handle_mouse()
{
	return (false);
}
