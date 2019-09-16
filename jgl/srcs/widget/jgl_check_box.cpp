#include "jgl.h"

/*c_check_box::c_check_box(c_widget *p_parent) : c_text_label(p_parent)
{
	checked = false;
	check_text_size();
}

void c_check_box::check_text_size()
{
	int inside_size = _viewport->size().x - _border_size * 6;
	int inside_height = _viewport->size().y - _border_size * 2;
	int delta[5] = {100, 50, 20, 10, 1};
	_text_size = 2;

	if (_text == "")
		return ;

	for (int i = 0; i < 5; i++)
	{
		while (calc_text_len(_text, _text_size + delta[i]) <= inside_size - (_text_size + delta[i]) * 1.5f &&
			   get_char('M', _text_size + delta[i])->size().y <= inside_height)
			_text_size += delta[i];
	}
}

void c_check_box::render_check_box()
{
	render_frame();

	draw_text(_viewport, _text, Vector2(_border_size * 2 + _text_size, _border_size), _text_size, _text_color, _text_style);
}

void c_check_box::render()
{
	_viewport->use();

	render_check_box();
}

bool c_check_box::handle_keyboard()
{
	return (false);
}

bool c_check_box::handle_mouse()
{
	return (false);
}*/
