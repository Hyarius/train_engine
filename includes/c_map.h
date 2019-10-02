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

	c_frame *_panel;
	c_text_label *_name_label;
	c_text_entry *_name_entry;

public:
	c_map(string path, c_widget *parent = nullptr);

	void add_city();
	void select_city(c_city *city);
	Vector2 convert_to_map_coord(Vector2 source);
	c_city *check_city();

	float zoom();
	Vector2 map_anchor();

	void update();

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);

	virtual void render();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
