#ifndef C_MILESTONE_H
#define C_MILESTONE_H

class c_milestone
{
private:
	int _nb;
	Vector2 _pos;
	class c_city* _place;

	float _distance;

	vector<class c_milestone*> _links;
	bool _linked;

public:
	c_milestone(Vector2 p_pos, class c_city *p_place = nullptr);
	~c_milestone();

	void add_link(class c_milestone* to_add);
	void remove_link(c_milestone *target);
	void remove_links();

	bool clicked(Vector2 mouse);
	bool is_accesible(c_milestone *destination);

	void set_distance(float p_distance) { _distance = p_distance; }
	void set_pos(Vector2 p_pos) { _pos = p_pos; }
	void set_place(class c_city* p_place) { _place = p_place; }
	void set_linked(bool p_linked) { _linked = p_linked; }

	bool &linked() { return (_linked); }
	float &distance() { return (_distance); }
	Vector2 &pos() { return (_pos); }
	class c_city* place() { return (_place); }

	vector<class c_milestone*> &links() { return (_links); }
	class c_milestone*links(size_t index) { return (_links[index]); }

	int nb(){return (_nb);}
	void draw();
	void draw_link();

	bool operator == (c_milestone& delta){if (_nb == delta.nb())return (true);return(false);}
};

namespace std
{
    template<> struct less<c_milestone>
    {
       const bool operator() (c_milestone& lhs, c_milestone& rhs) const
       {
           return (lhs.nb() < rhs.nb());
       }
    };
}

typedef pair<c_milestone *, c_milestone *> pair_milestone;

#endif
