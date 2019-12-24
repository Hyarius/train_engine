#ifndef EVENT_H
#define EVENT_H

struct Event
{
	string name;
	int nbr;
	float time;

	Event(string p_name = "Default", int p_nbr = 0, float p_time = 0.0f);
};

ostream& operator<<(ostream& os, Event &event);

#endif
