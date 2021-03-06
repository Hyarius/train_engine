#ifndef C_JOURNEY_H
#define C_JOURNEY_H

typedef pair<int, int> pair_int;

class c_journey
{
private:
	bool _exist;
	string _output_text;
	fstream _output_file;

	class c_train *_train;

	vector<c_milestone *> _path;
	vector<c_hour_entry *> _hour_panel;
	vector<c_frame *> _wait_panel;
	vector<c_text_label *> _wait_label;
	vector<c_value_entry *> _wait_entry;

public:
	c_journey();

	~c_journey();

	string &output_text(){return (_output_text);}
	string name();
	void create_output_file(string result_path, int simulation_index);
	void print_output_file();
	fstream &output_file(){return (_output_file);}

	void set_train(c_train *p_train){_train = p_train;}

	c_train *train(){return (_train);}
	void set_exist(bool p_exist){_exist = p_exist;}
	bool exist(){return (_exist);}
	vector<c_milestone *> &path(){return (_path);}
	vector<c_hour_entry *> &hour_panel(){return (_hour_panel);}
	vector<c_frame *> &wait_panel(){return (_wait_panel);}
	vector<c_text_label *> &wait_label(){return (_wait_label);}
	vector<c_value_entry *> &wait_entry(){return (_wait_entry);}

	c_milestone *path(size_t index){if (index >=_path.size())return (nullptr);return (_path[index]);}
	c_hour_entry *hour_panel(size_t index){if (index >=_path.size())return (nullptr);return (_hour_panel[index]);}
	c_frame *wait_panel(size_t index){if (index >=_path.size())return (nullptr);return (_wait_panel[index]);}
	c_text_label *wait_label(size_t index){if (index >=_path.size())return (nullptr);return (_wait_label[index]);}
	c_value_entry *wait_entry(size_t index){if (index >=_path.size())return (nullptr);return (_wait_entry[index]);}

	size_t get_index(c_milestone *target);
	c_rail *get_rail(size_t start_index);
	void calc_distance();

	void add_point(c_milestone *new_point, pair_int p_hour = pair_int(0, 0), int p_wait_time = 0);
	void remove_point();

	void actualize_panel(float zoom);
	void draw();
};

c_journey *load_journey(string path);
void create_journey_output_file(string result_path, int simulation_index, c_journey *journey, float time);
void create_journey_plot_output(string result_path, int simulation_index, c_plot *plot, float start_time, float end_time, float max_dist);

#endif
