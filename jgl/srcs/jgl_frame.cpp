#include "jgl.h"

using namespace std;

c_frame::c_frame(c_widget *p_parent, int p_border_size, c_color p_front, c_color p_back) : c_widget(p_parent)
{
	border_size = p_border_size;
	front = p_front;
	back = p_back;
}

void c_frame::render()
{
	if (is_active() == false)
		return ;

	fill_rectangle(_viewport, back, 0, _viewport->size());
	fill_rectangle(_viewport, front, border_size, _viewport->size() - border_size * 2);

	for (size_t i = 0; i < _childrens.size(); i++)
		_childrens[i]->render();
}

void c_frame::handle_keyboard()
{

}

void c_frame::handle_mouse()
{

}
