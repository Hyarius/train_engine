#ifndef C_TRAIN_ENGINE_H
#define C_TRAIN_ENGINE_H

#include "jgl.h"

extern map <string, bool> event_city_bool_map;
extern map <string, bool> event_rail_bool_map;
extern map <string, int> event_active_map;
extern map <string, vector<float>> event_active_map_time;

class c_train_engine
{
private:
	int _simulation_index;
	bool _plot_bool;
	bool _text_bool;

	c_plot *_plot;
	size_t _arrived_train;

	float _time;
	vector<float> _time_travel;
	vector<float> _base_time_travel;
	float _time_delta;

	vector<c_journey *> _journey_list;
	c_image * _graphic_output;
	vector<float> _distance;
	vector<float> _arrived_hour;

public:
	c_train_engine();

	void clean();
	void run(string result_path, int simulation_index, bool plot_bool, bool text_bool);
	void iterate(bool perturbation);
	bool is_late(float time = 0.0f);
	bool is_late(size_t i, float time = 0.0f);

	void intelligence(size_t index);
	float execution(size_t index, float time_left);

	void create_graphic_output();

	void draw_train_state(size_t i);
	string draw_train_information(size_t i);
	string draw_train_position(size_t i);

	float calc_distance_left(size_t index);
	float calc_next_speed(size_t index);

	bool should_slow(size_t index);
	bool can_overtake(size_t index);

	void move_train(size_t index, float distance);

	void calc_event(size_t index, float time);

	float calc_waiting_time(size_t index, float time_left);
	float calc_event_time(size_t index, float time_left);
	float calc_run_time(size_t index, float time_left);
	float calc_accelerate_time(size_t index, float time_left, float target_speed);
	float calc_decelerate_time(size_t index, float time_left, float target_speed);
	float calc_stoping_time(size_t index, float time_left);

	void add_journey(c_journey *new_journey);

	void set_time(int p_hour, int p_minute){_time = convert_int_to_hour(p_hour, p_minute);}
	void set_time(float p_time){_time = p_time;}
	void set_time_delta(int p_time_delta){_time_delta = p_time_delta / 60.0f;}

	float time(){return (_time);}
	float time_delta(){return (_time_delta);}
	c_train *train(size_t i){if (i >= _journey_list.size())return(nullptr);return (_journey_list[i]->train());}
	vector<c_journey *> &journey_list(){return (_journey_list);}
	vector<float> &distance(){return (_distance);}
	vector<float> &arrived_hour(){return (_arrived_hour);}
	vector<float> &time_travel(){return (_time_travel);}
	vector<float> &base_time_travel(){return (_base_time_travel);}
};

#endif
