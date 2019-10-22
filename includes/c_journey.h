#ifndef C_JOURNEY_H
#define C_JOURNEY_H

#include "c_milestone.h"

typedef pair<int, int> pair_int;

class c_journey
{
private:
	vector<c_milestone *> _path;
	vector<c_hour_entry *> _hour_panel;

public:
	c_journey();
	c_journey(string path);

	~c_journey();

	vector<c_milestone *> &path(){return (_path);}
	vector<c_hour_entry *> &hour_panel(){return (_hour_panel);}

	size_t get_index(c_milestone *target);

	void add_point(c_milestone *new_point, pair_int p_hour = pair_int(0, 0));

	void actualize_panel();
	void draw();
};

#endif
