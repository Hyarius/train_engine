#include "engine.h"

c_map::c_map(string path, c_widget *parent) : c_widget(parent)
{
	_map = c_image(path);
	_map_anchor = _map.size() / -2;
	_zoom = 1.0f;
	_selected = nullptr;
	_cities.clear();
}

void c_map::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{

}

void c_map::render()
{
	_viewport->use();
	_viewport->clear();

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
		cout << "Here" << endl;
}
