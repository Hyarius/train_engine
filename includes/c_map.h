#ifndef C_MAP_H
#define C_MAP_H

#include "jgl.h"
#include "c_city.h"

class c_map : public c_widget
{
private:
	c_image _map;
	Vector2 _map_anchor;
	float _zoom;

	c_city *_selected;

	vector<c_city *> _cities;

public:
	c_map(string path, c_widget *parent = nullptr);

	void add_city();
	void select_city(c_city *city);
	Vector2 convert_to_map_coord(Vector2 source);
	c_city *check_city();

	float zoom();
	Vector2 map_anchor();

	virtual void render();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
