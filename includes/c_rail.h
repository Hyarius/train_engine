#ifndef C_RAIL_H
#define C_RAIL_H

#include "jgl.h"

/*class c_rail
{
private:
	vector<class c_rail*> _prev;
	vector<class c_rail*> _next;

	Vector2 _start;
	Vector2 _end;

public:
	c_rail();

	void add_prev(class c_rail* p_prev) { _prev.push_back(p_prev); }
	void add_next(class c_rail* p_next) { _next.push_back(p_next); }
	void remove_prev(class c_rail* p_target);
	void remove_next(class c_rail* p_target);

	void set_start(Vector2 p_start) { _start = p_start; }
	void set_end(Vector2 p_end) { _end = p_end; }

	class c_rail* prev() { return (_prev); }
	class c_rail* next() { return (_next); }
	Vector2 start() { return (_start); }
	Vector2 end() { return (_end); }
	float distance() { return (sqrt(
		  pow(_end.x - _start.x, 2.0)
		+ pow(_end.y - _start.y, 2.0)));
	}
};*/

#endif