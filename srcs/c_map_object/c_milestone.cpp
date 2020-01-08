#include "engine.h"

#define MILE_SIZE 1.5f

int nb_index = 0;

c_milestone::c_milestone(Vector2 p_pos, c_city* p_place)
{
	_nb = nb_index;
	nb_index++;
	_pos = p_pos;
	_place = p_place;
	_distance = FLT_MAX;
	_linked = false;
}

c_milestone::~c_milestone()
{
	remove_links();
}

bool c_milestone::is_accesible(c_milestone *destination)
{
	auto key = pair_milestone(this, destination);

	if (g_map->rails().find(key) == g_map->rails().end())
		key = pair_milestone(destination, this);

	if (g_map->rails().find(key) == g_map->rails().end())
		return (false);

	return (true);
}

void c_milestone::add_link(c_milestone* to_add)
{
	if (to_add == this)
		return ;

	// pair_milestone key = pair_milestone(this, to_add);
	// pair_milestone inv_key = pair_milestone(to_add, this);
	//
	// if (map_contain<pair_milestone, c_rail *>(g_map->rails(), key) == true || map_contain<pair_milestone, c_rail *>(g_map->rails(), inv_key) == true)
	// 	return ;

	vector<c_milestone*>::iterator it;

	it = find(_links.begin(), _links.end(), to_add);
	if (it == _links.end())
	{
	 	_links.push_back(to_add);
	 	to_add->links().push_back(this);
		auto it2 = g_map->rails().find(pair_milestone(this, to_add));
		if (it2 == g_map->rails().end())
		{
	 		c_rail *rail = new c_rail(this, to_add);

			for (auto it = g_map->new_rail_event().begin(); it != g_map->new_rail_event().end(); it++)
				rail->add_event(new Event(it->second));

			g_map->rails()[pair_milestone(this, to_add)] = rail;
			g_map->rails()[pair_milestone(to_add, this)] = rail;
		}
	}
}

void c_milestone::remove_link(c_milestone *target)
{
	if (target == nullptr)
		return ;

	auto it = find(_links.begin(), _links.end(), target);

	if (it != _links.end())
	{
		_links.erase(it);

		auto it2 = find(target->links().begin(), target->links().end(), this);

		if (it2 != target->links().end())
			target->links().erase(it2);
	}
}

void c_milestone::remove_links()
{
	for (size_t i = 0; i < _links.size(); i++)
	{
		vector<c_milestone*> tmp = _links[i]->links();

		auto it = find(_links[i]->links().begin(), _links[i]->links().end(), this);

		if (it != _links[i]->links().end())
		{
			g_map->rails().erase(pair_milestone(*it, this));
			_links[i]->links().erase(it);
		}
	}
}

bool c_milestone::clicked(Vector2 mouse)
{
	Vector2 pos1, pos2, size1;

	size1 = MILE_SIZE * g_map->zoom();
	pos1 = g_map->anchor() + g_map->map_anchor() + g_map->area() / 2 + _pos * g_map->zoom() - size1 / 2;
	pos2 = pos1 + size1;

	if (mouse.x < pos1.x || mouse.x > pos2.x || mouse.y < pos1.y || mouse.y > pos2.y)
		return (false);

	return (true);
}

void c_milestone::draw()
{
	static Color p_color = Color(220, 220, 220);

	Vector2 pos1, size1;
	size1 = g_map->zoom() * MILE_SIZE;
	pos1 = g_map->convert_to_screen_coord(_pos);

	if (_pos != Vector2())
		fill_centred_rectangle(p_color, pos1, size1, g_map->viewport());
}

void c_milestone::draw_link()
{
	Vector2 pos1 = g_map->convert_to_screen_coord(_pos);

	for (size_t i = 0; i < _links.size(); i++)
	{
		auto target = pair_milestone(this, _links[i]);
		if (g_map->rails()[target] != nullptr && this == g_map->rails()[target]->pos1())
	 		g_map->rails()[target]->poly()->set_pos(pos1);

		c_milestone *tmp_mile = _links[i];
		Vector2 tmp2 = tmp_mile->pos();

		Vector2 pos2 = g_map->convert_to_screen_coord(_links[i]->pos());

		if (g_map->rails()[target] != nullptr &&
			g_map->rails()[target]->state() == true)
		{
			draw_line(Color(42, 10, 168), pos1, pos2, 8, g_map->viewport());
		}
		else
			draw_line(Color(202, 199, 212), pos1, pos2, 4, g_map->viewport());

	}
}
