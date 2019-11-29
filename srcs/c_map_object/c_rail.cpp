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
	e_channel_state type;

	c_journey *journey = train->journey();
	size_t journey_index = train->index();

	// if (journey->path(journey_index) == _pos1)
	// 	cout << "Rail moving even direction" << endl;

	_train_list.push_back(train);
}

void c_rail::remove_train(c_train *p_train)
{
	size_t index;

	index = 0;
	while (index < _train_list.size() && _train_list[index] != p_train)
		index++;

	if (index != _train_list.size())
		_train_list.erase(_train_list.begin() + index);
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
