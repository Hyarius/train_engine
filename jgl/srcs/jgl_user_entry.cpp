#include "jgl.h"

c_user_entry::c_user_entry(c_widget *p_parent) : c_frame(p_parent, 3, c_color(165, 165, 165), c_color(185, 185, 185))
{
	text = "ceci est un text";
}

void c_user_entry::render()
{
	if (is_active() == false)
		return ;

	fill_rectangle(_viewport, back, 0, _viewport->size());
	fill_rectangle(_viewport, front, border_size, _viewport->size() - border_size * 2);
	draw_text(_viewport, text, border_size, _viewport->size().y - (border_size) * 2, BLACK, NORMAL);

	for (size_t i = 0; i < _childrens.size(); i++)
		_childrens[i]->render();
}

void c_user_entry::handle_keyboard()
{

}

void c_user_entry::handle_mouse()
{

}
