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
	remove_links();
}

bool c_milestone::is_accesible(c_milestone *destination)
{
	auto key = pair_milestone(this, destination);

	if (_map->rails().find(key) == _map->rails().end())
		key = pair_milestone(destination, this);

	if (_map->rails().find(key) == _map->rails().end())
		return (false);

	return (true);
}

void c_milestone::add_link(c_milestone* to_add)
{
	if (to_add == this)
		return ;

	if (_map->rails().find(pair_milestone(this, to_add)) != _map->rails().end() ||
		_map->rails().find(pair_milestone(to_add, this)) != _map->rails().end())
		return ;

	vector<c_milestone*>::iterator it;

	it = find(_links_to.begin(), _links_to.end(), to_add);
	if (it == _links_to.end())
	{
		_links_to.push_back(to_add);
		to_add->links_from().push_back(this);
		auto it2 = _map->rails().find(pair_milestone(this, to_add));
		if (it2 == _map->rails().end())
		{
			c_rail *rail = new c_rail(this->pos(), to_add->pos());
			_map->rails()[pair_milestone(this, to_add)] = rail;
			_map->rails()[pair_milestone(to_add, this)] = rail;
		}
	}
}

void c_milestone::remove_link(c_milestone *target)
{
	if (target == nullptr)
		return ;

	auto it = find(_links_to.begin(), _links_to.end(), target);

	if (it != _links_to.end())
	{
		_links_to.erase(it);

		auto it2 = find(target->links_from().begin(), target->links_from().end(), this);

		if (it2 != target->links_from().end())
			target->links_from().erase(it2);
	}
}

void c_milestone::remove_links()
{
	for (size_t i = 0; i < _links_from.size(); i++)
	{
		vector<c_milestone*> tmp = _links_from[i]->links_to();

		auto it = find(_links_from[i]->links_to().begin(), _links_from[i]->links_to().end(), this);

		if (it != _links_from[i]->links_to().end())
		{
			_map->rails().erase(pair_milestone(*it, this));
			_links_from[i]->links_to().erase(it);
		}
	}
	for (size_t i = 0; i < _links_to.size(); i++)
	{
		auto it = find(_links_to[i]->links_from().begin(), _links_to[i]->links_from().end(), this);

		if (it != _links_to[i]->links_from().end())
		{
			_map->rails().erase(pair_milestone(this, *it));
			_links_to[i]->links_from().erase(it);
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
		fill_centred_rectangle(_map->viewport(), p_color, pos1, size1);
}

void c_milestone::draw_link()
{
	if (_map == nullptr)
		return;

	Vector2 pos1 = _map->convert_to_screen_coord(_pos);

	for (size_t i = 0; i < _links_to.size(); i++)
	{
		auto target = pair_milestone(this, _links_to[i]);
		if (_map->rails()[target] != nullptr)
	 		_map->rails()[target]->poly()->set_pos(pos1);

		c_milestone *tmp_mile = _links_to[i];
		Vector2 tmp2 = tmp_mile->pos();
		c_map *tmp_m = _map;

		Vector2 pos2 = _map->convert_to_screen_coord(_links_to[i]->pos());

		if (_map->rails()[target] != nullptr &&
			_map->rails()[target]->state() == true)
		{
			draw_line(_map->viewport(), Color(42, 10, 168), pos1, pos2, 8);
		}
		else
			draw_line(_map->viewport(), Color(202, 199, 212), pos1, pos2, 4);

	}
}
