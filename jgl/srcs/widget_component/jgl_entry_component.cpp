#include "jgl.h"

w_entry_component::w_entry_component()
{
	_text = "";
	_cursor = text.size();
	_selected = false;
}


void w_entry_component::select()
{
	selected = true;
}

void w_entry_component::unselect()
{
	selected = false;
}


void w_entry_component::move_cursor(int delta)
{

}

void w_entry_component::add_text(string new_part)
{
	if (text.size() == 0 || g_application->event()->text.text[0] != text[_cursor - 1])
	{
		text.insert(cursor, g_application->event()->text.text);
		_cursor++;
	}
}

void w_entry_component::remove_text()
{
	if (_cursor > 0 && text.size() != 0)
	{
		_cursor--;
		text.erase(cursor);
	}
}

virtual void w_entry_component::render()
{

}
