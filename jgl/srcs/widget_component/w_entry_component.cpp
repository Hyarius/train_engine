#include "jgl.h"

w_entry_component::w_entry_component(
	Vector2 p_anchor, Vector2 p_area,
	int p_size, string p_text,
	alignment p_align, text_color p_color, text_style p_style)
{
	_text = p_text;
	_cursor = 0;
	_text_to_draw = p_text;
	_cursor_to_draw = 0;
	_anchor = p_anchor;
	_area = p_area;
	_align = p_align;
	_size = p_size;
	_color = p_color;
	_style = p_style;
}

w_entry_component::~w_entry_component()
{

}

void w_entry_component::calc_text_size()
{
	int delta[5] = {100, 50, 20, 10, 1};
	_size = 2;

	for (int i = 0; i < 5; i++)
	{
		while (get_char('M', _size + delta[i])->size().y <= _area.y)
			_size += delta[i];
	}
}

void w_entry_component::move_cursor(int delta)
{
	if ((delta > 0 && _cursor < _text.size()) || (delta < 0 && _cursor > 0))
	{
		_cursor += delta;
		calc_text_to_draw();
	}
}

void w_entry_component::add_text(string new_text)
{
	_text.insert(_cursor, new_text);
	_cursor++;
	calc_text_to_draw();
}

void w_entry_component::remove_text()
{
	if (_cursor > 0 && _text.size() != 0)
	{
		_cursor--;
		_text.erase(_cursor);
		calc_text_to_draw();
	}
}

void w_entry_component::calc_text_to_draw()
{
	_text_to_draw = "";
	_cursor_to_draw = 0;

	int i = _cursor;

	if (_text != "")
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

void w_entry_component::render(c_viewport *viewport)
{
	Vector2 pos;

	if (_align == alignment::left)
	{
		pos.x = calc_text_len(_text_to_draw, _size) / 2.0f;
		pos.y = _area.y / 2.0f;
	}
	else if (_align == alignment::centred)
	{
		pos = _area / 2;
	}
	else if (_align == alignment::right)
	{
		pos.x = _area.x - calc_text_len(_text_to_draw, _size) / 2.0f;
		pos.y = _area.y / 2.0f;
	}
	draw_centred_text(viewport, _text_to_draw, pos, _size, _color, _style);
}
