#include "engine.h"

Event::Event(string p_name, int p_nb_event, float p_time)
{
	event_name = p_name;
	nb_event = p_nb_event;
	time = p_time;
}

ostream& operator<<(ostream& os, Event &event)
{
	os << event.event_name << " : [" << to_string(event.nb_event) << "][" << convert_minute_to_hour(event.time) << "]";
	return (os);
}
