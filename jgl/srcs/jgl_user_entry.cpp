#include "jgl.h"

c_user_entry::c_user_entry(c_widget *p_parent) : c_frame(p_parent, 3, Color(165, 165, 165), Color(185, 185, 185))
{
	text = "";
	cursor = text.size();
	selected = false;

	next_input = 0;
	input_delay = 100;
}

void c_user_entry::render()
{
	Vector2 pos;
	int	text_size;

	_viewport->viewport();

	fill_rectangle(_viewport, back, 0, _viewport->size());
	fill_rectangle(_viewport, front, border_size, _viewport->size() - border_size * 2);

	text_size = _viewport->size().y - (border_size) * 2;

	int nb_char = max_char_in_box(_viewport->size().x - border_size * 2, text_size);

	cout << "Nb char : " << nb_char << endl;
	pos = border_size;
	if (text.size() != 0)
		pos.x = draw_text(_viewport, text.substr(0, cursor), pos, text_size);
	pos.x += 3;

	if (selected == true && (SDL_GetTicks() / 400) % 2 == 0)
		fill_rectangle(_viewport, Color(50, 50, 50), pos + Vector2(0, 3), Vector2(2, text_size - 3));

	if (cursor < text.size())
		if (text.size() != 0)
			draw_text(_viewport, text.substr(cursor), pos, text_size);
}

bool c_user_entry::handle_keyboard()
{
	if (selected == false)
		return (false);

	if (g_keyboard->get_key(SDL_SCANCODE_LEFT))
	{
		if (cursor > 0)
			cursor--;
		g_keyboard->reset_key(SDL_SCANCODE_LEFT);
	}
	else if (g_keyboard->get_key(SDL_SCANCODE_RIGHT))
	{
		if (cursor < text.size())
			cursor++;
		g_keyboard->reset_key(SDL_SCANCODE_RIGHT);
	}
	else if (g_keyboard->get_key(SDL_SCANCODE_BACKSPACE))
	{
		if (cursor > 0)
		{
			cursor--;
			text.erase(cursor);
		}
		g_keyboard->reset_key(SDL_SCANCODE_BACKSPACE);
	}

	if (g_application->event()->type == SDL_TEXTINPUT)
	{
		Uint32 time = SDL_GetTicks();
		if (text.size() == 0 || g_application->event()->text.text[0] != text[cursor - 1] || time >= next_input)
		{
			text.insert(cursor, g_application->event()->text.text);
			next_input = time + input_delay;
			cursor++;
		}
	}

	return (false);
}

void c_user_entry::select()
{
	selected = true;
}

void c_user_entry::unselect()
{
	selected = false;
}

bool c_user_entry::handle_mouse()
{
	if (g_mouse->get_button(MOUSE_LEFT) == MOUSE_DOWN)
		unselect();

	if (g_mouse->get_button(MOUSE_LEFT) == MOUSE_UP)
	{
		if (is_clicked(g_mouse->pos) == true)
		{
			select();
			return (true);
		}
	}
	return (false);
}
