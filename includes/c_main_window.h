#ifndef C_MAIN_WINDOW_H
#define C_MAIN_WINDOW_H

#include "jgl.h"
#include "c_map.h"

class c_main_window
{
private:
	// - Boxes
	c_frame *map_box;
	c_frame *train_box;
	c_frame *command_box;
	c_frame *config_box;
	c_frame *travel_box;

	// - Map
	c_map *map;

	// - Command
	c_button *start_button;
	c_hour_entry *hour_entry;

	// - Config

public:
	c_main_window();

	void create_box();
	void create_map_panel();
	void create_command_panel();
	void create_config_panel();
	void create_travel_panel();
	void create_train_panel();
};

#endif
