#include "jgl.h"

w_value_entry_component::w_value_entry_component(c_widget *p_owner, float p_value) :
		w_component(p_owner), w_graphical_component(), w_textual_component()
{
	_value = p_value;
	_text = ftoa(_value);
	_cursor = _text.length();
	_text_to_draw = _text;
	_cursor_to_draw = 0;
	_anchor = Vector2();
	_area = Vector2();
	_align = alignment::left;
	_size = 16;
	_color = text_color::black;
	_style = text_style::normal;
}

void w_value_entry_component::calc_text_to_draw()
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

void w_value_entry_component::move_cursor(int delta)
{
	if ((delta > 0 && _cursor < _text.size()) || (delta < 0 && _cursor > 0))
	{
		_cursor += delta;
		calc_text_to_draw();
	}
}

void w_value_entry_component::add_text(string new_text)
{
	if (string_is_numeric(new_text) == false)
		return ;

	_text.insert(_cursor, new_text);
	_cursor++;
	calc_text_to_draw();
}

void w_value_entry_component::remove_text()
{
	if (_cursor > 0 && _text.size() != 0)
	{
		_cursor--;
		_text.erase(_cursor);
		calc_text_to_draw();
	}
}

void w_value_entry_component::render(c_viewport *viewport)
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
	draw_centred_text(viewport, _text_to_draw, pos + _anchor - viewport->anchor(), _size, _color, _style);
}
