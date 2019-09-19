#include "jgl.h"

w_entry_component::w_entry_component(
	Vector2 p_anchor, Vector2 p_area,
	int p_size, string p_text,
	alignment p_align, text_color p_color, text_style p_style)
{
	_text = p_text;
	_cursor = p_text.size();
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


void w_entry_component::render(c_viewport *viewport)
{

}
