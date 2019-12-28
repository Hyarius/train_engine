#ifndef C_MAP_H
#define C_MAP_H

#include "jgl.h"

enum class e_map_state
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
	c_tileset *_point_image;
	Vector2 _map_anchor;
	float _zoom;
	float _scale_unit;

	c_city *_city_selected;
	vector<c_rail *> _rail_selected;
	c_milestone *_mile_selected;

	vector<c_city*> _cities;
	vector<c_milestone*> _milestones;
	c_journey *_journey;
	map<pair_milestone, c_rail *> _rails;
	//map<c_milestone *, map<c_milestone *, c_rail *> > _rails;

	c_text_label *_unit_label;
	c_value_entry *_landmark_scale;
	c_button *_calib_button;
	e_map_state _state;

	c_frame *_rail_panel;
	c_text_label *_rail_speed_label;
	c_value_entry *_rail_speed_entry;
	c_text_label *_rail_canton_label;
	c_value_entry *_rail_canton_entry;
	c_check_box *_rail_dual_ways_box;
	c_check_box *_rail_even_overtake_box;
	c_check_box *_rail_odd_overtake_box;

	c_frame *_city_panel;
	c_text_label *_city_name_label;
	c_text_entry *_city_name_entry;
	c_text_label *_city_nb_channel_label;
	c_value_entry *_city_nb_channel_entry;
	c_frame *_city_event_panel;
	c_button *_city_add_event_button;
	c_button *_city_remove_event_button;
	vector<c_text_label *>_city_event_name_entry;
	vector<c_value_entry *>_city_nb_event_entry;
	vector<c_value_entry *>_city_event_duration_entry;
	c_vscroll_bar *_event_scroll_bar;

	c_frame *_create_event_frame;
	c_button *_create_valid_button;
	c_button *_create_cancel_button;
	c_text_label *_create_event_name_label;
	c_text_label *_create_event_nbr_label;
	c_text_label *_create_event_time_label;
	c_text_entry *_create_event_name_entry;
	c_value_entry *_create_event_nbr_entry;
	c_value_entry *_create_event_time_entry;

	c_frame *_delete_event_frame;
	c_button *_delete_valid_button;
	c_button *_delete_cancel_button;
	c_frame *_delete_event_scroll_area;
	c_vscroll_bar *_delete_scroll_bar;
	c_text_label *_delete_event_label;
	vector<c_check_box *>_delete_event_selector;

	float _rel_distance;
	Vector2 _landmark1;
	Vector2 _landmark2;

public:
	/*---------------------*/
	//Constructor
	c_map(string path, c_widget *parent = nullptr);

	void reload_map(string path);
	void create_city_panel();
	void create_message_box();
	void create_rail_panel();
	void create_calib_button();
	void create_landmark();

	/*---------------------*/
	//Setter
	void set_state(e_map_state new_state){_state = new_state;}
	void set_journey(c_journey *p_journey){_journey = p_journey;}

	//Getter
	c_journey *journey(){return (_journey);}
	c_tileset *point_image(){return (_point_image);}
	vector<c_city *> &cities(){return (_cities);}
	c_city *cities(size_t index){return (_cities[index]);}
	vector<c_milestone *> &milestones(){return (_milestones);}
	c_milestone *milestones(size_t index){return (_milestones[index]);}
	map<pair_milestone, c_rail *> &rails(){return (_rails);}
	float zoom(){return (_zoom);}
	float scale_unit(){return (_scale_unit);}
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

		//Rail part
	void select_city(c_city *city);
	void select_rail(c_rail *rail);
	void remove_rail(c_rail *rail);

		//Milestone part
	c_milestone *add_milestone(c_city* p_city);
	void remove_milestone(c_milestone* to_remove);
	float milestone_distance(c_milestone *point_a, c_milestone *point_b);
	size_t get_milestone_id(c_milestone *target);
	c_milestone *get_milestone(size_t index);

		//City part
	c_city* add_city();
	void remove_city(c_city* to_remove);

		//Landmark part
	void place_landmark(Vector2 new_pos, int index = -1);
	void reset_landmark(){_landmark1 = Vector2();_landmark2 = Vector2();}


	/*---------------------*/
	//Control
	void control_city_creation(c_city* city);
	void control_milestone_creation();
	void control_rail_edition(c_rail *rail);

	bool control_unselect();

	bool control_calibration();
	bool control_travel_definition();
	bool control_normal();

	bool control_mouvement();
	bool control_zoom();


	/*---------------------*/
	void start_calculation(vector<c_journey *> journeys);
	void calc_duration(c_journey *to_calc);
	vector<c_milestone *> calc_path(c_milestone *start, c_milestone *target);
	void create_new_path();
	void open_journey(string path);
	void remove_path(c_milestone *target);

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

	c_frame *create_event_frame(){return (_create_event_frame);}
	c_frame *delete_event_frame(){return (_delete_event_frame);}
	vector<c_check_box *> &delete_event_selector(){return (_delete_event_selector);}
	c_check_box *delete_event_selector(size_t i){if (i < 0 || i >= _delete_event_selector.size()) return (nullptr);return (_delete_event_selector[i]);}

	void add_event_to_list(Event *event);
	void add_event_to_list_delete(Event *event);
	void add_event_to_cities(Event *event);
	Event *get_event();
	void reset_event_list();
	void parse_event_list();
};

//Saving functions
void save_city(Data data);
void save_milestone(Data data);
void save_rail(Data data);

extern c_map *g_map;

#endif
