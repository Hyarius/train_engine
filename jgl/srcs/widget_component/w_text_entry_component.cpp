#include "jgl.h"

w_text_entry_component::w_text_entry_component(c_widget *p_owner, string p_text) :
		w_component(p_owner), w_graphical_component(), w_textual_component()
{
	_text = p_text;
	_cursor = 0;
	_text_to_draw = p_text;
	_cursor_to_draw = 0;
	_area = Vector2();
	_anchor = Vector2();
	_align = alignment::left;
	_size = 16;
	_color = text_color::black;
	_style = text_style::normal;
}


void w_text_entry_component::move_cursor(int delta)
{
	if ((delta > 0 && _cursor < _text.size()) || (delta < 0 && _cursor > 0))
	{
		_cursor += delta;
		calc_text_to_draw();
	}
}

void w_text_entry_component::add_text(string new_text)
{
	_text.insert(_cursor, new_text);
	_cursor++;
	calc_text_to_draw();
}

void w_text_entry_component::change_text(string new_text)
{
	for (size_t i = 0; i < new_text.size() && i + _cursor < _text.size(); i++)
		_text[_cursor + i] = new_text[i];

	_cursor++;
	calc_text_to_draw();
}

void w_text_entry_component::remove_text()
{
	if (_cursor > 0 && _text.size() != 0)
	{
		_cursor--;
		_text.erase(_text.begin() + _cursor, _text.begin() + _cursor + 1);
		calc_text_to_draw();
	}
}

void w_text_entry_component::supp_text()
{
	if (_cursor > 0 && _cursor < _text.size() && _text.size() != 0)
	{
		_text.erase(_text.begin() + _cursor, _text.begin() + _cursor + 1);
		calc_text_to_draw();
	}
}

void w_text_entry_component::calc_text_to_draw()
{
	_text_to_draw = "";
	_cursor_to_draw = 0;

	int i = _cursor;

	if (_text.empty() == false)
	{
		while (i > 0 && calc_text_len(_text_to_draw + _text[i - 1], _size) < _area.x)
		{
			i--;
			_text_to_draw = _text.substr(i, _cursor);
		}

		_cursor_to_draw = _cursor - i;
		i = _cursor;

		while (i < _text.size() && calc_text_len(_text_to_draw + _text[i], _size) < _area.x)
		{
			_text_to_draw += _text[i];
			i++;
		}
	}
}

void w_text_entry_component::render(c_viewport *viewport)
{
	Vector2 pos;

	if (_align == alignment::left)
	{
		pos.x = 0;
		pos.y = 0;
	}
	else if (_align == alignment::centred)
	{
		pos.x = _area.x / 2 - calc_text_len(_text_to_draw, _size) / 2.0f;
		pos.y = 0;
	}
	else if (_align == alignment::right)
	{
		pos.x = _area.x - calc_text_len(_text_to_draw, _size);
		pos.y = 0;
	}

	pos += _anchor;

	draw_text(_text_to_draw, pos, _size, _color, _style, viewport);

	pos.x += calc_text_len(_text_to_draw.substr(0, _cursor_to_draw), _size);

	if (_selected == true && (SDL_GetTicks() / 400) % 2 == 0)
		fill_rectangle(Color(50, 50, 50), pos, Vector2(2, _size), viewport);
}
