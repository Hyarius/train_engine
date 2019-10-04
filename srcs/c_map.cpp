#include "engine.h"

c_map::c_map(string path, c_widget *parent) : c_widget(parent)
{
	_map = c_image(path);
	_map_anchor = _map.size() / -2;
	_zoom = 1.0f;
	_selected = nullptr;
	_mile_selected = nullptr;
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
	_name_entry->entry().set_align(alignment::centred);
	_name_entry->active();
}

void c_map::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{

	_zoom = 1.0f;
	while (_map.size().x * _zoom < p_area.x)
		_zoom += 0.2f;

	_map_anchor = (_map.size() * _zoom) / -2;

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

	for (size_t i = 0; i < _milestones.size(); i++)
		_milestones[i]->draw_link();

	for (size_t i = 0; i < _milestones.size(); i++)
		_milestones[i]->draw();

	for (size_t i = 0; i < _cities.size(); i++)
		_cities[i]->draw_name();
}

bool c_map::handle_keyboard()
{
	return (false);
}

void c_map::select_city(c_city *city)
{
	if (_selected != nullptr)
		_selected->select(false);

	_selected = city;
	if (_selected != nullptr)
		_selected->select(true);

	_panel->set_active(!(city == nullptr));
	if (_selected != nullptr)
		_name_entry->entry().set_text(_selected->name());
}

Vector2 c_map::convert_to_map_coord(Vector2 source)
{
	return (((source - _viewport->anchor()) - (_map_anchor + size() / 2.0f)) / _zoom);
}

Vector2 c_map::convert_to_screen_coord(Vector2 source)
{
	return (map_anchor() + size() / 2 + source * zoom());
}

c_milestone *c_map::add_milestone(c_city* p_city)
{
	Vector2 pos = convert_to_map_coord(g_mouse->pos);
	c_milestone* new_milestone = new c_milestone(this, pos, p_city);

	_milestones.push_back(new_milestone);

	if (p_city != nullptr)
		p_city->set_milestone(new_milestone);

	return (new_milestone);
}

c_city *c_map::add_city()
{
	Vector2 pos = convert_to_map_coord(g_mouse->pos);

	c_city *new_city = new c_city(this, pos);
	_cities.push_back(new_city);

	add_milestone(new_city);

	return (new_city);
}

void c_map::remove_city(c_city* to_remove)
{
	remove_milestone(to_remove->milestone());

	to_remove->set_milestone(nullptr);

	vector<c_city *>::iterator it;

	it = find(_cities.begin(), _cities.end(), to_remove);
	if (it != _cities.end())
	{
		delete to_remove;
		_cities.erase(it);
	}
}

void c_map::remove_milestone(c_milestone* to_remove)
{

	vector<c_milestone*>::iterator it;

	it = find(_milestones.begin(), _milestones.end(), to_remove);
	if (it != _milestones.end())
	{
		delete to_remove;
		_milestones.erase(it);
	}
}

c_city* c_map::check_city()
{
	for (size_t i = 0; i < _cities.size(); i++)
		if (_cities[i]->clicked(g_mouse->pos) == true)
			return (_cities[i]);

	return (nullptr);
}

c_milestone* c_map::check_milestone()
{
	for (size_t i = 0; i < _milestones.size(); i++)
		if (_milestones[i]->clicked(g_mouse->pos) == true)
			return (_milestones[i]);

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
