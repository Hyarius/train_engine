#include "jgl.h"

c_check_box::c_check_box(string p_text, bool p_state, c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(Vector2(), Vector2(), 3);
	_text = w_text_component(p_text);
	_text.set_align(alignment::centred);

	_check = w_check_component(Vector2(), Vector2(), p_state);
	_check.set_check(Color(70, 150, 255));
}

c_check_box::~c_check_box()
{

}

void c_check_box::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	_box.set_area(p_area);
	_box.set_anchor(p_anchor);

	Vector2 check_area = p_area.y - _box.border() * 4;
	Vector2 text_area;
	text_area.x = p_area.x - check_area.x - _box.border() * 3;
	text_area.y = p_area.y - _box.border() * 2;

	_text.set_area(text_area);
	_text.set_anchor(p_anchor + _box.border());
	_text.calc_text_size();

	_check.set_area(check_area);
	_check.set_anchor(p_area - _box.border() * 2 - check_area);
}

void c_check_box::render()
{
	_box.render(_viewport);
	_text.render(_viewport);
	_check.render(_viewport);
}

bool c_check_box::handle_mouse()
{
	if (g_mouse->get_button(mouse_button::left) == mouse_state::up && is_pointed(g_mouse->pos))
	{
		_check.set_state(!_check.state());
		return (true);
	}
	return (false);
}

bool c_check_box::handle_keyboard()
{
	return (false);
}
