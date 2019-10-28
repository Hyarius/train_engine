#ifndef C_CITY_H
#define C_CITY_H

#include "jgl.h"

class c_city
{
private:
	class c_milestone* _milestone;
	string _name;
	Vector2 _pos;
	int _selected;

public:
	c_city(Vector2 p_pos = Vector2());
	~c_city();

	class c_milestone* milestone() { return (_milestone); }
	string &name(){return (_name);}
	Vector2 pos(){return (_pos);}

	void set_milestone(class c_milestone* p_milestone) { _milestone = p_milestone; }
	void set_name(string new_name){_name = new_name;}
	void set_pos(Vector2 new_pos){_pos = new_pos;}
	void draw();
	void draw_name();
	bool is_here(Vector2 p_pos);
	bool clicked(Vector2 mouse);
	void select(bool state);
};

#endif
