#ifndef EVENT_TYPE_H
#define EVENT_TYPE_H

enum class city_event_type
{
	alarm_signal_in = 0,
	alarm_signal_out = 1,
	blocking_door = 2,
	human_trouble = 3,
	animal_trouble = 4,
	intrusion = 5,
	fire = 6,
};

#define NB_CITY_EVENT 7

enum class rail_event_type
{
	main_way_trouble = 0,
	signal_trouble = 1,
	position_system_trouble = 2,
	catenary_trouble = 3,
	traction_trouble = 4,
	under_station_trouble = 5,
	switch_trouble = 6,
};

#define NB_RAIL_EVENT 7

#endif
