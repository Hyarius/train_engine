#ifndef C_MAP_H
#define C_MAP_H

#include "jgl.h"
#include "c_city.h"
#include "c_milestone.h"
#include "c_rail.h"

enum map_state
{
	normal = 0,
	calibration = 1,
	travel_definition = 2
};

class c_map : public c_widget
{
private:
	string _map_path;
	c_image *_map;
	Vector2 _map_anchor;
	float _zoom;
	float _scale_unit;

	c_city *_city_selected;
	vector<c_rail *> _rail_selected;
	c_milestone *_mile_selected;

	vector<c_city*> _cities;
	vector<c_milestone*> _milestones;
	vector<c_milestone*> _path;
	map<pair<c_milestone *, c_milestone *>, c_rail *> _rails;
	//map<c_milestone *, map<c_milestone *, c_rail *> > _rails;

	c_text_label *_unit_label;
	c_value_entry *_landmark_scale;
	c_button *_calib_button;
	map_state _state;

	c_frame *_rail_panel;
	c_text_label *_rail_speed_label;
	c_value_entry *_rail_speed_entry;

	c_frame *_city_panel;
	c_text_label *_city_name_label;
	c_text_entry *_city_name_entry;
	c_text_label *_city_waiting_label;
	c_value_entry *_city_waiting_entry;

	float _rel_distance;
	Vector2 _landmark1;
	Vector2 _landmark2;

public:
	/*---------------------*/
	//Constructor
	c_map(string path, c_widget *parent = nullptr);

	void reload_map(string path);
	void create_city_panel();
	void create_rail_panel();
	void create_calib_button();
	void create_landmark();

	/*---------------------*/
	//Setter
	void set_state(map_state new_state){_state = new_state;}

	//Getter
	vector<c_city *> &cities(){return (_cities);}
	vector<c_milestone *> &milestones(){return (_milestones);}
	map<pair<c_milestone *, c_milestone *>, c_rail *> &rails(){return (_rails);}
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
	c_rail *check_rail();
	c_milestone *check_milestone();
	c_city *check_city();

		//Milestone part
	void select_city(c_city *city);
	void select_rail(c_rail *rail);

		//Milestone part
	c_milestone *add_milestone(c_city* p_city);
	void remove_milestone(c_milestone* to_remove);
	float milestone_distance(c_milestone *point_a, c_milestone *point_b);

		//City part
	c_city* add_city();
	void remove_city(c_city* to_remove);

		//Landmark part
	void place_landmark(Vector2 new_pos, int index = -1);
	void reset_landmark(){_landmark1 = Vector2();_landmark2 = Vector2();}


	/*---------------------*/
	//Control
	void control_city_creation();
	void control_milestone_creation();
	void control_rail_edition(c_rail *rail);

	bool control_unselect();

	bool control_calibration();
	bool control_travel_definition();
	bool control_normal();

	bool control_mouvement();
	bool control_zoom();


	/*---------------------*/
	void start_calculation();
	void calc_duration();

	/*---------------------*/

	//Load functions
	void load_cities(fstream &file);
	void load_milestones(fstream &file);
	void load_rails(fstream &file);

	void load_city(fstream &file);
	void load_milestone(fstream &file);
	void load_rail(fstream &file);

	void load_map(string path);

	/*---------------------*/
	//Widget functions
	void update();
	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
	void set_geometry_city_panel();
	void set_geometry_rail_panel();
	void render();
	bool handle_keyboard();
	bool handle_mouse();
	void quit();
};

//Saving functions
void save_city(Data data);
void save_milestone(Data data);
void save_rail(Data data);

#endif
