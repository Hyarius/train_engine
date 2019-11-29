#include "engine.h"

c_rail::c_rail(c_milestone *pos1, c_milestone *pos2)
{
	_distance = -1;
	_speed = 145.0f;
	_cantonal_dist = 2.0f;
	_train_list.clear();
	_pos1 = pos1;
	_pos2 = pos2;

	_channel.resize(NB_CHANNEL_TYPE);
	_channel[0] = 2;
	for (size_t i = 1; i < NB_CHANNEL_TYPE; i++)
		_channel[i] = 0;

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

void c_rail::add_train(c_train *train)
{
	e_channel_state type = get_way(train->journey()->path(train->index()));
	add_channel(type);
	remove_channel(type);
	_train_list.push_back(train);
}

void c_rail::remove_train(c_train *train)
{
	if (train == nullptr)
		return ;

	size_t index;

	index = 0;
	while (index < _train_list.size() && _train_list[index] != train)
		index++;

	if (index != _train_list.size())
		_train_list.erase(_train_list.begin() + index);

	e_channel_state type = get_way(train->journey()->path(train->index()));
	remove_channel(type);
	bool find = false;
	add_channel(e_channel_state::empty);
}

e_channel_state c_rail::get_way(c_milestone *start)
{
	if (start == _pos1)
		return (e_channel_state::even);
	else if (start == _pos2)
		return (e_channel_state::odd);
	return (e_channel_state::error);
}

void c_rail::set_nb_channel(size_t index)
{
	_channel[0] = index;
	_channel[1] = 0;
	_channel[2] = 0;
}

void c_rail::add_channel(e_channel_state p_state)
{
	(_channel[static_cast<int>(p_state)])++;
}

void c_rail::remove_channel(e_channel_state p_state)
{
	(_channel[static_cast<int>(p_state)])--;
}

void c_rail::reset_channel(e_channel_state p_old, e_channel_state p_new)
{
	add_channel(p_old);
	remove_channel(p_new);
}

bool c_rail::can_go(e_channel_state p_state)
{
	if (_channel[static_cast<int>(p_state)] != 0)
		return (true);
	return (false);
}
