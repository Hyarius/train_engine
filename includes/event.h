#ifndef EVENT_H
#define EVENT_H

#define SEC_PER_YEAR 31536000

struct Event
{
	string name;
	int nbr;
	float time;

	Event(string p_name = "Default", int p_nbr = 0, float p_time = 0.0f);
	Event(Event *copy){name = copy->name;nbr = copy->nbr;time = copy->time;}
};

ostream& operator<<(ostream& os, Event &event);

#endif
