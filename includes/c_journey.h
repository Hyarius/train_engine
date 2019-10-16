#ifndef C_JOURNEY_H
#define C_JOURNEY_H

#include "c_milestone.h"

typedef pair<int, int> pair_int;

class c_journey
{
private:
	c_map *_map;

	vector<c_milestone *> _path;
	vector<pair_int> _schedule;

public:
	c_journey(c_map *p_map);

	vector<c_milestone *> &path(){return (_path);}
	vector<pair_int> &schedule(){return (_schedule);}

	void add_point(c_milestone *new_point, pair_int new_point_shedule = pair_int(-1, -1));

	void draw();
};

#endif
