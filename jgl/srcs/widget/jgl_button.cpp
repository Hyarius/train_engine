#include "jgl.h"

c_button::c_button(c_widget *p_parent, t_funct p_funct, Data p_param) : c_text_label(p_parent)
{
	funct = p_funct;
	param = p_param;
	timer = 0;
}

void c_button::render()
{
	_viewport->use();

	if (timer > 0)
	{
		fill_rectangle(_viewport, _back + Color(50, 50, 50, 100), 0, _viewport->size());
		fill_rectangle(_viewport, _front + Color(50, 50, 50, 100), _border_size, _viewport->size() - _border_size * 2);
		timer--;
	}
	else
	{
		fill_rectangle(_viewport, _back, 0, _viewport->size());
		fill_rectangle(_viewport, _front, _border_size, _viewport->size() - _border_size * 2);
	}

	draw_centred_text(_viewport, _text, _viewport->size() / 2, _text_size, _text_color, _text_style);
}

bool c_button::handle_keyboard()
{
	return (false);
}

bool c_button::handle_mouse()
{
	if (g_mouse->get_button(MOUSE_LEFT) == MOUSE_DOWN && is_pointed(g_mouse->pos))
		timer = 12;

	if (g_mouse->get_button(MOUSE_LEFT) == MOUSE_UP && is_pointed(g_mouse->pos))
	{
		if (funct != nullptr)
			funct(param);
	}

	return (false);
}
