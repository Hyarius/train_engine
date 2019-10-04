#ifndef C_MAP_H
#define C_MAP_H

#include "jgl.h"
#include "c_city.h"
#include "c_milestone.h"
#include "c_rail.h"

class c_map : public c_widget
{
private:
	c_image _map;
	Vector2 _map_anchor;
	float _zoom;

	c_city *_selected;
	c_milestone *_mile_selected;

	vector<c_city*> _cities;
	vector<c_milestone*> _milestones;

	c_frame *_panel;
	c_text_label *_name_label;
	c_text_entry *_name_entry;

public:
	c_map();
	c_map(string path, c_widget *parent = nullptr);

	c_milestone *add_milestone(c_city* p_city);
	c_city* add_city();
	void remove_city(c_city* to_remove);
	void remove_milestone(c_milestone* to_remove);
	void select_city(c_city *city);
	Vector2 convert_to_map_coord(Vector2 source);
	Vector2 convert_to_screen_coord(Vector2 source);
	c_city* check_city();
	c_milestone* check_milestone();

	float zoom();
	Vector2 map_anchor();

	bool control_click();
	bool control_mouvement();
	bool control_zoom();

	void update();

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);

	virtual void render();

	virtual bool handle_keyboard();

	virtual bool handle_mouse();
};

#endif
