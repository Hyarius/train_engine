#include "engine.h"

void c_main_window::create_command_panel()
{
	int border = command_box->box().border();
	Vector2 button_pos = border * 1;
	Vector2 button_size = Vector2(command_box->box().area().x - border * 4,
		(command_box->box().area().y - border * 3) / 2 - border);

	start_button = new c_button(nullptr, nullptr, command_box);
	start_button->text().set_text("Start simulation");
	start_button->set_geometry(button_pos, button_size);
	start_button->active();

	Vector2 hour_pos = button_pos + Vector2(0.0f, button_size.y + border);
	Vector2 hour_size = button_size;

	hour_entry = new c_hour_entry(12.0f, 0.0f, command_box);

	hour_entry->set_geometry(hour_pos, hour_size);
	hour_entry->active();
}
