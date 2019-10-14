#ifndef C_MILESTONE_H
#define C_MILESTONE_H

class c_milestone
{
private:
	class c_map* _map;
	Vector2 _pos;
	class c_city* _place;

	vector<class c_milestone*> _links_to;
	vector<class c_milestone*> _links_from;

public:
	c_milestone(class c_map* p_map, Vector2 p_pos, class c_city *p_place = nullptr);
	~c_milestone();

	void add_link(class c_milestone* to_add);
	void remove_link(c_milestone *target);
	void remove_links();

	bool clicked(Vector2 mouse);
	bool is_accesible(c_milestone *destination);

	void set_pos(Vector2 p_pos) { _pos = p_pos; }
	void set_place(class c_city* p_place) { _place = p_place; }
	void set_map(class c_map* p_map) { _map = p_map; }

	Vector2 &pos() { return (_pos); }
	class c_city* place() { return (_place); }
	class c_map* map() { return(_map); }
	vector<class c_milestone*> &links_to() { return (_links_to); }
	vector<class c_milestone*> &links_from() { return (_links_from); }

	void draw();
	void draw_link();

};

namespace std
{
    template<> struct less<c_milestone>
    {
       const bool operator() (c_milestone& lhs, c_milestone& rhs) const
       {
           return (lhs.pos() < rhs.pos());
       }
    };
}

#endif
