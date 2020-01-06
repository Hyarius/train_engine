#ifndef C_MAIN_WINDOW_H
#define C_MAIN_WINDOW_H

#include "jgl.h"

class c_main_window
{
public:
	c_tileset *tileset;

	// - Boxes
	c_frame *map_box;
	c_frame *train_box;
	c_frame *command_box;
	c_frame *config_box;
	c_frame *travel_box;

	// - Map
	c_map *map;

	// - Train
	c_frame *train_box_frame;
	c_text_label *train_box_label;
	c_text_label *train_value_label[3];
	c_value_entry *train_value_entry[3];

	// - Command
	c_train_engine *engine;
	c_button *start_button;
	c_text_label *nb_value_label;
	c_value_entry *nb_value_entry;
	c_text_label *interval_value_label;
	c_value_entry *interval_value_entry;
	c_check_box *graph_result_check;
	c_check_box *text_result_check;

	// - Config

	// - Travel
	c_button *new_button;
	c_button *save_button;
	c_button *load_button;
	c_button *erase_button;
	c_frame *travel_panel;
	c_vscroll_bar *scroll_bar;
	vector<c_check_box *> travel_name;

	c_main_window();

	void create_box();
	void create_map_panel();
	void create_command_panel();
	void create_config_panel();
	void create_travel_panel();
	void create_train_panel();

	void load_travel_checkbox();
};

extern c_main_window main_window;

#endif
