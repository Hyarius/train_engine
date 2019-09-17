#include "jgl.h"

w_entry_component::w_entry_component()
{
	_text = "";
	_cursor = _text.size();
	_selected = false;
}

int w_entry_component::cursor()
{
	return (_cursor);
}

string w_entry_component::text()
{
	return (_text);
}

bool w_entry_component::selected()
{
	return (_selected);
}

void w_entry_component::select()
{
	_selected = true;
}

void w_entry_component::unselect()
{
	_selected = false;
}

void w_entry_component::move_cursor(int delta)
{
	if ((delta > 0 && _cursor < _text.size()) || (delta < 0 && _cursor > 0))
		_cursor += delta;
}

void w_entry_component::add_text(string new_text)
{
	_text.insert(_cursor, new_text);
	_cursor++;
}

void w_entry_component::remove_text()
{
	if (_cursor > 0 && _text.size() != 0)
	{
		_cursor--;
		_text.erase(_cursor);
	}
}

void w_entry_component::render(c_viewport *viewport, Vector2 area, int text_size, int delta)
{
	string text_to_draw = "";
	int draw_cursor = 0;
	Vector2 pos = delta;
	int i = _cursor;

	if (_text != "")
	{
		while (i > 0 && calc_text_len(text_to_draw + _text[i - 1], text_size) < area.x)
		{
			i--;
			text_to_draw = _text.substr(i, _cursor);
		}

		draw_cursor = _cursor - i;
		i = _cursor;

		while (i < _text.size() && calc_text_len(text_to_draw + _text[i], text_size) < area.x)
		{
			text_to_draw += _text[i];
			i++;
		}

		draw_text(viewport, text_to_draw, pos, text_size);

		pos.x += calc_text_len(text_to_draw.substr(0, draw_cursor), text_size);
	}


	if (_selected == true && (SDL_GetTicks() / 400) % 2 == 0)
		fill_rectangle(viewport, Color(50, 50, 50), pos + Vector2(0, 2), Vector2(2, text_size - 3));
}
