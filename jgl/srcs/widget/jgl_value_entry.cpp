#include "jgl.h"

c_value_entry::c_value_entry(float p_value, c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component();
	_entry = w_value_entry_component(p_value);

	_select = false;
	_next_input = 0;
	_input_delay = 100;
}

c_value_entry::~c_value_entry()
{

}

void c_value_entry::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	_box.set_area(p_area);
	_box.set_anchor(p_anchor);
	_entry.set_area(p_area - _box.border() * 4);
	_entry.set_anchor(p_anchor + _box.border() * 2);
	_entry.calc_text_size();
}

void c_value_entry::render()
{
	_box.render(_viewport);
	_entry.render(_viewport);
}

bool c_value_entry::handle_mouse()
{
	if (g_mouse->get_button(mouse_button::left) == mouse_state::down)
		unselect();

	if (g_mouse->get_button(mouse_button::left) == mouse_state::up)
	{
		if (is_pointed(g_mouse->pos) == true)
		{
			select();
			return (true);
		}
	}
	return (false);
}

bool c_value_entry::handle_keyboard()
{
	if (selected() == false)
		return (false);

	if (g_keyboard->get_key(SDL_SCANCODE_LEFT))
	{
		_entry.move_cursor(-1);
		g_keyboard->reset_key(SDL_SCANCODE_LEFT);
	}
	else if (g_keyboard->get_key(SDL_SCANCODE_RIGHT))
	{
		_entry.move_cursor(1);
		g_keyboard->reset_key(SDL_SCANCODE_RIGHT);
	}
	else if (g_keyboard->get_key(SDL_SCANCODE_BACKSPACE))
	{
		_entry.remove_text();
		g_keyboard->reset_key(SDL_SCANCODE_BACKSPACE);
	}

	if (g_application->event()->type == SDL_TEXTINPUT)
	{
		Uint32 time = SDL_GetTicks();
		if (g_application->event()->text.text[0] != _entry.text()[_entry.cursor() - 1] ||
			time >= _next_input)
		{
			_entry.add_text(g_application->event()->text.text);
			_next_input = time + _input_delay;
		}
	}

	return (false);
}
