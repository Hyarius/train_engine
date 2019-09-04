#include "jgl.h"

using namespace std;

c_window::c_window(c_widget *p_parent, c_color p_back) : c_widget(p_parent)
{
	back = p_back;
}

void c_window::render()
{
	if (is_active() == false)
		return ;

	fill_rectangle(_viewport, back, 0, _viewport->size());

	for (size_t i = 0; i < _childrens.size(); i++)
		_childrens[i]->render();
}

void c_window::handle_keyboard()
{

}

void c_window::handle_mouse()
{

}
