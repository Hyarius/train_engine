#include "jgl.h"

c_hour_entry::c_hour_entry(float p_hour, float p_minute, c_widget *p_parent) : c_widget(p_parent)
{
	_box = w_box_component(this);
	_label = w_text_component(this, ":");
	_hour = w_value_entry_component(this, p_hour);
	_minute = w_value_entry_component(this, p_minute);
}

c_hour_entry::~c_hour_entry()
{

}

void c_hour_entry::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	_box.set_area(p_area);
	_box.set_anchor(p_anchor);

	_label.set_area(p_area - _box.border() * 2);
	_label.set_anchor(p_anchor + _box.border());
	_label.set_align(alignment::centred);
	_label.calc_text_size(_label.area());

	Vector2 number_size = (p_area - _box.border() * 2) / Vector2(2, 1) - Vector2(_box.border() * 2, 0);
	Vector2 hour_pos = p_anchor + _box.border();
	Vector2 minute_pos = hour_pos + Vector2(number_size.x + _box.border() * 4, 0.0f);

	_hour.set_area(number_size);
	_hour.set_align(alignment::right);
	_hour.calc_text_size_height(_hour.area());
	_hour.calc_text_to_draw();
	_hour.set_anchor(hour_pos);

	_minute.set_area(number_size);
	//_minute.set_text("00");
	_minute.calc_text_size_height(_minute.area());
	_minute.calc_text_to_draw();
	_minute.set_anchor(minute_pos);
}

void c_hour_entry::render()
{
	_box.render(_viewport);
	_label.render(_viewport);
	while (_hour.text().size() < 2)
		_hour.set_text("0" + _hour.text());
	_hour.render(_viewport);
	while (_minute.text().size() < 2)
		_minute.set_text("0" + _minute.text());
	_minute.render(_viewport);
}

bool c_hour_entry::handle_mouse()
{
	return (false);
}

bool c_hour_entry::handle_keyboard()
{
	return (false);
}
