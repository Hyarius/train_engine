#ifndef EVENT_H
#define EVENT_H

struct Event
{
	string event_name;
	int nb_event;
	float time;

	Event(string p_name = "Default", int p_nb_event = 0, float p_time = 0.0f);
};

ostream& operator<<(ostream& os, Event &event);

#endif
