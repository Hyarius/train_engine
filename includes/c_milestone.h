#ifndef C_MILESTONE_H
#define C_MILESTONE_H

class c_milestone
{
private:
	class c_map* _map;
	Vector2 _pos;
	class c_city* _place;

	vector<class c_milestone*> _links_to;
	vector<class c_rail*> _rails;
	vector<class c_milestone*> _links_from;

public:
	c_milestone(class c_map* p_map, Vector2 p_pos, class c_city *p_place = nullptr);
	~c_milestone();

	void add_link(class c_milestone* to_add);
	void remove_link();

	bool clicked(Vector2 mouse);

	void set_pos(Vector2 p_pos) { _pos = p_pos; }
	void set_place(class c_city* p_place) { _place = p_place; }
	void set_place(class c_map* p_map) { _map = p_map; }

	Vector2 &pos() { return (_pos); }
	class c_city* place() { return (_place); }
	class c_map* map() { return(_map); }
	vector<class c_milestone*> *links_to() { return (&_links_to); }
	vector<class c_rail*> *rails() { return (&_rails); }
	vector<class c_milestone*> *links_from() { return (&_links_from); }

	void draw();
	void draw_link();
};

#endif
