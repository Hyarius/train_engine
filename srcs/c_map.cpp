#include "engine.h"

c_map::c_map(string path, c_widget *parent) : c_widget(parent)
{
	_map = c_image(path);
	_map_anchor = _map.size() / -2;
	_zoom = 1.0f;
	_selected = nullptr;
	_cities.clear();

	_panel = nullptr;
	_name_label = nullptr;
	_name_entry = nullptr;

	_panel = new c_frame(this);

	_name_label = new c_text_label("City name :", _panel);
	_name_label->label().set_align(alignment::left);
	_name_label->label().set_style(text_style::underline);
	_name_label->active();

	_name_entry = new c_text_entry("", _panel);
	_name_entry->entry().set_align(alignment::left);
	_name_entry->active();
}

void c_map::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	Vector2 panel_anchor = Vector2(10, 10);
	Vector2 panel_size = Vector2(300, 500);//p_area.x / 4, p_area.y / 3);
	_panel->set_geometry(panel_anchor, panel_size);

	Vector2 name_anchor = Vector2(5, 5);
	Vector2 name_size = Vector2(80, 30);//p_area.x / 4, p_area.y / 3);
	_name_label->set_geometry(name_anchor, name_size);

	Vector2 entry_anchor = Vector2(10 + name_size.x, 0.0f) + name_anchor;
	Vector2 entry_size = Vector2(panel_size.x - name_size.x - 20, name_size.y);//p_area.x / 4, p_area.y / 3);
	_name_entry->set_geometry(entry_anchor, entry_size);
}

void c_map::render()
{
	_viewport->use();

	_map.draw(_viewport, _map_anchor + size() / 2.0f, _map.size() * _zoom);

	for (size_t i = 0; i < _cities.size(); i++)
		_cities[i]->draw();
}

bool c_map::handle_keyboard()
{
	return (false);
}

void c_map::select_city(c_city *city)
{
	_selected = city;
	_panel->set_active(!(city == nullptr));
	if (_selected != nullptr)
	{
		_name_entry->entry().set_text(_selected->name());
	}
}

Vector2 c_map::convert_to_map_coord(Vector2 source)
{
	return (((source - _viewport->anchor()) - (_map_anchor + size() / 2.0f)) / _zoom);
}

void c_map::add_city()
{
	Vector2 pos = convert_to_map_coord(g_mouse->pos);

	c_city *new_city = new c_city(this, pos);
	//select_city(new_city);
	_cities.push_back(new_city);
	//new_city->select();
}

c_city *c_map::check_city()
{
	for (size_t i = 0; i < _cities.size(); i++)
		if (_cities[i]->clicked(g_mouse->pos) == true)
			return (_cities[i]);

	return (nullptr);
}

float c_map::zoom()
{
	return (_zoom);
}

Vector2 c_map::map_anchor()
{
	return (_map_anchor);
}

void c_map::update()
{
	if (_selected != nullptr)
	{
		_selected->set_name(_name_entry->entry().text());
		// cout << "name : [" << _name_entry->entry().text() << "]" << endl;
		// cout << "Size : [" << _name_entry->entry().size() << "]" << endl;
	}
}
