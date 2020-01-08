#include "engine.h"

c_rail::c_rail()
{
	_distance = -1;
	_speed = 145.0f;
	_dual_ways = true;
	_cantonal_dist = 2.0f;
	_pos1 = nullptr;
	_pos2 = nullptr;
	_state = false;
	_poly = nullptr;
}

c_rail::c_rail(c_milestone *pos1, c_milestone *pos2)
{
	_distance = -1;
	_speed = 145.0f;
	_dual_ways = true;
	_cantonal_dist = 2.0f;
	_pos1 = pos1;
	_pos2 = pos2;

	_state = false;

	_poly = new Polygon2D(0);

	Vector2 start = 0;
	Vector2 end = pos2->pos() - pos1->pos();
	Vector2 trans = pos2->pos().cross(pos1->pos()).normalize();

	Vector2 pos[4];

	pos[0] = start + (trans * 0.8f);
	pos[1] = start - (trans * 0.8f);
	pos[2] = end + trans * 0.8f;
	pos[3] = end - trans * 0.8f;

	for (int i = 0; i < 4; i++)
		_poly->add_point(pos[i]);

	_poly->add_side(0, 1);
	_poly->add_side(2, 0);
	_poly->add_side(1, 3);
	_poly->add_side(3, 2);
}

void c_rail::set_milestones(c_milestone *pos1, c_milestone *pos2)
{
	_pos1 = pos1;
	_pos2 = pos2;

	_poly = new Polygon2D(0);

	Vector2 start = 0;
	Vector2 end = _pos2->pos() - _pos1->pos();
	Vector2 trans = _pos2->pos().cross(_pos1->pos()).normalize();

	Vector2 pos[4];

	pos[0] = start + (trans * 0.8f);
	pos[1] = start - (trans * 0.8f);
	pos[2] = end + trans * 0.8f;
	pos[3] = end - trans * 0.8f;

	for (int i = 0; i < 4; i++)
		_poly->add_point(pos[i]);

	_poly->add_side(0, 1);
	_poly->add_side(2, 0);
	_poly->add_side(1, 3);
	_poly->add_side(3, 2);
}

vector<c_train *> &c_rail::train_list(e_way_type p_type)
{
	size_t index = static_cast<int>(p_type);

	return (_ways[index].train_list());
}

static size_t get_way_id(c_way *ways, c_train *train)
{
	size_t index;

	if (ways[0].type() == train->get_way_type())
		index = 0;
	else
		index = 1;

	return (index);
}

void c_rail::add_train(c_train *train)
{
	if (train == nullptr || train->journey() == nullptr)
		return ;

	_ways[get_way_id(_ways, train)].add_train(train);
}

void c_rail::remove_train(c_train *train)
{
	if (train == nullptr)
		return ;

	_ways[get_way_id(_ways, train)].remove_train(train);
}

ostream& operator<<(ostream& os, c_rail *rail)
{
	os << *rail;
	return os;
}

void c_rail::add_event(Event *event)
{
	if (map_contain(event_list(), event->name) == true)
		return ;

	event_rail_bool_map[event->name] = true;
	_event_list[event->name] = event;
}

ostream& operator<<(ostream& os, c_rail &rail)
{
	os << "=======" << endl;
	os << "Rail event " << endl;
	for (auto i = rail.event_list().begin(); i != rail.event_list().end(); i++)
		os << i->second->name << endl;
	os << "=======" << endl;
	return os;
}
