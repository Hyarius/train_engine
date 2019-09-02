#ifndef C_MAP_H
#define C_MAP_H

#include "jgl.h"

class c_map : public c_widget
{
private:
	c_image map;
	Vector2 anchor;
	float zoom;

	vector<Vector2> points;

public:
	c_map(string path, c_widget *parent = NULL);

	void add_city();

	virtual void render();

	virtual void handle_keyboard();

	virtual void handle_mouse();
};

#endif
