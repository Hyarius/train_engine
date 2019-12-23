#ifndef C_CITY_H
#define C_CITY_H

#include "jgl.h"

class c_city
{
private:
	class c_milestone* _milestone;
	string _name;
	int _nb_channel;
	int _train_waiting;
	Vector2 _pos;
	int _selected;

	vector<Event> _event_list;

public:
	c_city(Vector2 p_pos = Vector2());
	~c_city();

	class c_milestone* milestone() { return (_milestone); }
	string &name(){return (_name);}
	vector<Event> &event_list(){return (_event_list);}
	Event &event_list(size_t i){if (i >= _event_list.size())return (_event_list[0]);return (_event_list[i]);}
	Vector2 pos(){return (_pos);}
	int nb_channel(){return (_nb_channel);}
	int train_waiting(){return (_train_waiting);}

	void set_milestone(class c_milestone* p_milestone) { _milestone = p_milestone; }
	void set_name(string new_name){_name = new_name;}
	void set_pos(Vector2 new_pos){_pos = new_pos;}
	void set_train_waiting(int new_train_waiting){_train_waiting = new_train_waiting;}
	void add_train_waiting(){_train_waiting++;}
	void remove_train_waiting(){_train_waiting--;}
	void set_nb_channel(int new_nb_channel){_nb_channel = new_nb_channel;}

	void draw();
	void draw_name();
	bool is_here(Vector2 p_pos);
	bool clicked(Vector2 mouse);
	void select(bool state);
};

ostream& operator<<(ostream& os, c_city *city);
ostream& operator<<(ostream& os, c_city &city);

#endif
