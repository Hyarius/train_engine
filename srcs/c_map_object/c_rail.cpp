#include "engine.h"

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

vector<c_train *> &c_rail::train_list(e_way_type p_type)
{
	size_t index = static_cast<int>(p_type);

	return (_ways[index].train_list());
}

void c_rail::add_train(c_train *train)
{
	size_t index;

	if (train == nullptr || train->journey() == nullptr)
		return ;

	if (_ways[0].type() == train->get_way_type())
		index = 0;
	else
		index = 1;

	_ways[index].add_train(train);
}

void c_rail::remove_train(c_train *train)
{
	size_t index;

	if (train == nullptr)
		return ;

	if (_ways[0].type() == train->get_way_type())
		index = 0;
	else
		index = 1;

	_ways[index].remove_train(train);
}
