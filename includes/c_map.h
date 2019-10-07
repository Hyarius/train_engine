#ifndef C_MAP_H
#define C_MAP_H

#include "jgl.h"
#include "c_city.h"
#include "c_milestone.h"
#include "c_rail.h"

enum map_state
{
	normal = 0,
	calibration = 1
};

class c_map : public c_widget
{
private:
	c_image *_map;
	Vector2 _map_anchor;
	float _zoom;
	float _scale_unit;

	c_city *_city_selected;
	c_milestone *_mile_selected;

	vector<c_city*> _cities;
	vector<c_milestone*> _milestones;

	c_text_label *_unit_label;
	c_value_entry *_landmark_scale;
	c_button *_calib_button;
	map_state _state;

	c_frame *_panel;
	c_text_label *_name_label;
	c_text_entry *_name_entry;

	float _rel_distance;
	Vector2 _landmark1;
	Vector2 _landmark2;

public:
	/*---------------------*/
	//Constructor
	c_map(string path, c_widget *parent = nullptr);

	void create_panel();
	void create_calib_button();
	void create_landmark();

	/*---------------------*/
	//Setter
	void set_state(map_state new_state){_state = new_state;}

	//Getter
	float zoom(){return (_zoom);}
	Vector2 map_anchor(){return (_map_anchor);}


	/*---------------------*/
	//Convert
	Vector2 convert_to_map_coord(Vector2 source);
	Vector2 convert_to_screen_coord(Vector2 source);
	void calc_distance_ratio();

	/*---------------------*/
	//Action
		//Detection part
	c_city* check_city();
	c_milestone* check_milestone();

		//Milestone part
	c_milestone *add_milestone(c_city* p_city);
	void remove_milestone(c_milestone* to_remove);
	float milestone_distance(c_milestone *point_a, c_milestone *point_b);

		//City part
	void select_city(c_city *city);
	c_city* add_city();
	void remove_city(c_city* to_remove);

		//Landmark part
	void place_landmark(Vector2 new_pos);
	void reset_landmark(){_landmark1 = Vector2();_landmark2 = Vector2();}


	/*---------------------*/
	//Control
	bool control_calibration();
	bool control_normal();

	bool control_mouvement();
	bool control_zoom();


	/*---------------------*/
	//Widget functions
	void update();
	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
	void render();
	bool handle_keyboard();
	bool handle_mouse();
};

#endif
