#ifndef C_JOURNEY_H
#define C_JOURNEY_H

typedef pair<int, int> pair_int;

class c_journey
{
private:
	fstream _output_file;

	vector<c_milestone *> _path;
	vector<c_hour_entry *> _hour_panel;
	vector<c_frame *> _wait_panel;
	vector<c_text_label *> _wait_label;
	vector<c_value_entry *> _wait_entry;

public:
	c_journey();
	c_journey(string path);

	~c_journey();

	string name();
	void create_output_file();
	void close_output_file();
	fstream &output_file(){return (_output_file);}
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
	e_channel_state travel_direction(size_t index);

	size_t get_index(c_milestone *target);
	c_rail *get_rail(size_t start_index);
	void calc_distance();

	void add_point(c_milestone *new_point, pair_int p_hour = pair_int(0, 0), int p_wait_time = 0);
	void remove_point();

	void actualize_panel();
	void draw();
};

#endif
