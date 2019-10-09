#include "engine.h"

#define MILE_SIZE 1.5f

c_milestone::c_milestone(c_map *p_map, Vector2 p_pos, c_city* p_place)
{
	_map = p_map;
	_pos = p_pos;
	_place = p_place;
}

c_milestone::~c_milestone()
{
	remove_link();
}

void c_milestone::add_link(c_milestone* to_add)
{
	vector<c_milestone*>::iterator it;

	it = find(_links_to.begin(), _links_to.end(), to_add);
	if (it == _links_to.end())
	{
		_links_to.push_back(to_add);
		to_add->links_from()->push_back(this);
		if (_map->rails()[this][to_add] == nullptr)
		{
			c_rail *rail;

			rail = new c_rail(this->pos(), to_add->pos());

			_map->rails()[this][to_add] = rail;

		}
	}
}

void c_milestone::remove_link()
{
	for (size_t i = 0; i < _links_from.size(); i++)
	{
		vector<c_milestone*>* tmp = _links_from[i]->links_to();

		auto it = find(tmp->begin(), tmp->end(), this);

		if (it != tmp->end())
		{
			_map->rails()[*it][this] = nullptr;
			tmp->erase(it);
		}
	}
	for (size_t i = 0; i < _links_to.size(); i++)
	{
		vector<c_milestone*>* tmp = _links_to[i]->links_from();

		auto it = find(tmp->begin(), tmp->end(), this);

		if (it != tmp->end())
		{
			_map->rails()[this][*it] = nullptr;
			tmp->erase(it);
		}
	}
}

bool c_milestone::clicked(Vector2 mouse)
{
	if (_map == nullptr)
		return false;

	Vector2 pos1, pos2, size1;

	size1 = MILE_SIZE * _map->zoom();
	pos1 = _map->anchor() + _map->map_anchor() + _map->size() / 2 + _pos * _map->zoom() - size1 / 2;
	pos2 = pos1 + size1;

	if (mouse.x < pos1.x || mouse.x > pos2.x || mouse.y < pos1.y || mouse.y > pos2.y)
		return (false);

	return (true);
}

void c_milestone::draw()
{
	static Color p_color = Color(220, 220, 220);

	if (_map == nullptr)
		return;

	Vector2 pos1, size1;
	size1 = _map->zoom() * MILE_SIZE;
	pos1 = _map->convert_to_screen_coord(_pos);

	if (_pos != Vector2())
	{
		fill_centred_rectangle(_map->viewport(), p_color, pos1, size1);
	}
}

void c_milestone::draw_link()
{
	if (_map == nullptr)
		return;

	Vector2 pos1 = _map->convert_to_screen_coord(_pos);

	for (size_t i = 0; i < _links_to.size(); i++)
	{
		if (_map->rails()[this][_links_to[i]] != nullptr)
	 		_map->rails()[this][_links_to[i]]->poly()->draw(_map->viewport(), Color(255, 0, 0), pos1, _map->zoom());

		Vector2 pos2 = _map->convert_to_screen_coord(_links_to[i]->pos());

		vector<c_milestone*> *tmp = _links_to[i]->links_to();
		if (find(tmp->begin(), tmp->end(), this) != tmp->end())
			draw_line(_map->viewport(), Color(255, 0, 150), pos1, pos2, 3);
		else
			draw_line(_map->viewport(), Color(150, 255, 0), pos1, pos2, 3);
	}
}
