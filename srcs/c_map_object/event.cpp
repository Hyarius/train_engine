#include "engine.h"

Event::Event(string p_name, int p_nbr, float p_time)
{
	name = p_name;
	nbr = p_nbr;
	time = p_time;
}

ostream& operator<<(ostream& os, Event &event)
{
	os << event.name << " : [" << to_string(event.nbr) << "][" << convert_minute_to_hour(event.time) << "]";
	return (os);
}
