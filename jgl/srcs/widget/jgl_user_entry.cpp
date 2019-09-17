#include "jgl.h"

c_user_entry::c_user_entry(int p_border_size, Color p_back,
			Color p_front, c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(p_border_size, p_back, p_front);
	_entry = w_entry_component();

	next_input = 0;
	input_delay = 100;
}

void c_user_entry::render()
{
	Vector2 area = _viewport->size() - _box.border_size() * 6;
	int text_size = _viewport->size().y - _box.border_size() * 3;

	_viewport->use();

	_box.render(_viewport, 0, _viewport->size());

	_entry.render(_viewport, area, text_size, _box.border_size());
}

bool c_user_entry::handle_keyboard()
{
	if (_entry.selected() == false)
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
			time >= next_input)
		{
			_entry.add_text(g_application->event()->text.text);
			next_input = time + input_delay;
		}
	}

	return (false);
}

bool c_user_entry::handle_mouse()
{
	if (g_mouse->get_button(MOUSE_LEFT) == MOUSE_DOWN)
		_entry.unselect();

	if (g_mouse->get_button(MOUSE_LEFT) == MOUSE_UP)
	{
		if (is_pointed(g_mouse->pos) == true)
		{
			_entry.select();
			return (true);
		}
	}
	return (false);
}
