#ifndef C_RAIL_H
#define C_RAIL_H

#include "jgl.h"
#include "c_milestone.h"

enum class e_way_type
{
	even = 0,
	odd = 1,
	error = 2
};

class c_way
{
private:
	e_way_type _type;
	bool _overtake;
	vector<class c_train *> _train_list;

public:
	c_way()
	{
		_type = e_way_type::even;
		_overtake = false;
		_train_list.resize(0);
		_train_list.clear();
	}
	~c_way(){}

	void set_type(e_way_type p_type){_type = p_type;}
	void set_overtake(bool p_overtake){_overtake = p_overtake;}

	void add_train(class c_train *p_train)
	{
		_train_list.push_back(p_train);
	}
	void remove_train(class c_train *p_train)
	{
		size_t index;

		index = 0;
		while (index < _train_list.size() && _train_list[index] != p_train)
			index++;

		if (index != _train_list.size())
			_train_list.erase(_train_list.begin() + index);
	}

	e_way_type type(){return (_type);}
	bool overtake(){return (_overtake);}
	vector<class c_train *> &train_list(){return (_train_list);}
};

class c_rail
{
private:
	float _speed;
	Polygon2D *_poly;

	bool _dual_ways;
	c_way _ways[2];

	float _cantonal_dist;

	c_milestone *_pos1;
	c_milestone *_pos2;
	float _distance;

	bool _state;

	map<string, Event *> _event_list;

public:
	c_rail(c_milestone *pos1, c_milestone *pos2);

	void add_train(class c_train *p_train);
	void remove_train(class c_train *p_train);

	map<string, Event *> &event_list(){return (_event_list);}
	void add_event(Event *event);
	Event *event_list(string key){return (_event_list[key]);}

	void set_state(bool p_state){_state = p_state;}
	void set_way_overtake(e_way_type type, bool state){_ways[static_cast<int>(type)].set_overtake(state);}
	void set_dual_ways(bool p_dual_ways){_dual_ways = p_dual_ways;}
	void set_cantonal_dist(float p_cantonal_dist){_cantonal_dist = p_cantonal_dist;}
	void set_pos1(c_milestone *p_pos1){_pos1 = p_pos1;}
	void set_pos2(c_milestone *p_pos2){_pos2 = p_pos2;}
	void calc_distance(float p_ratio){_distance = _pos1->pos().distance(_pos2->pos()) * p_ratio;}
	void set_speed(float p_speed){_speed = p_speed;}

	bool state(){return (_state);}
	bool way_overtake(e_way_type type){return (_ways[static_cast<int>(type)].overtake());}
	bool dual_ways(){return (_dual_ways);}
	float cantonal_dist(){return (_cantonal_dist);}
	c_milestone *pos1(){return (_pos1);}
	c_milestone *pos2(){return (_pos2);}
	float distance(){return (_distance);}
	float speed(){return (_speed);}

	c_way *ways(){return (_ways);}
	c_way &ways(size_t index){return (_ways[index]);}
	vector<class c_train *> &train_list(e_way_type p_type);

	void set_poly(Polygon2D *p_poly){_poly = p_poly;}
	Polygon2D *poly(){return (_poly);}
};

ostream& operator<<(ostream& os, c_rail *rail);
ostream& operator<<(ostream& os, c_rail &rail);

#endif
