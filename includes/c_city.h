#ifndef C_CITY_H
#define C_CITY_H

#include "jgl.h"

class c_city
{
private:
	class c_map *_map;
	class c_milestone* _milestone;
	string _name;
	int _waiting_time;
	Vector2 _pos;
	int _selected;

public:
	c_city(class c_map *p_map, Vector2 p_pos = Vector2());
	~c_city();

	class c_milestone* milestone() { return (_milestone); }
	string &name(){return (_name);}
	Vector2 pos(){return (_pos);}
	int waiting_time(){return (_waiting_time);}

	void set_waiting_time(int new_waiting_time){_waiting_time = new_waiting_time;}
	void set_milestone(class c_milestone* p_milestone) { _milestone = p_milestone; }
	void set_name(string new_name){_name = new_name;}
	void draw();
	void draw_name();
	bool clicked(Vector2 mouse);
	void select(bool state);
};

#endif
