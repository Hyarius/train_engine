#ifndef C_MAP_H
#define C_MAP_H

class c_map : public c_widget
{
private:
	c_image map;
	Vector2 anchor;
	float zoom;

public:
	c_map(string path, c_widget *parent = NULL) : c_widget(parent)
	{
		map = c_image(path);
		anchor = Vector2(0, 0);//_viewport->size() / 2 - map.size() / 2;
		zoom = 1;
	}

	virtual void render()
	{
		_viewport->clear();

		map.draw(_viewport, anchor * zoom, map.size() * zoom);

		for (size_t i = 0; i < _childrens.size(); i++)
			_childrens[i]->render();
	}

	virtual void handle_keyboard()
	{
		if (main_window->get_key(SDL_SCANCODE_E) == true)
			cout << "Key E pressed" << endl;
		if (main_window->get_key(SDL_SCANCODE_W) == true)
			cout << "Key W pressed" << endl;
		if (main_window->get_key(SDL_SCANCODE_Q) == true)
			cout << "Key Q pressed" << endl;
		if (main_window->get_key(SDL_SCANCODE_R) == true)
			cout << "Key R pressed" << endl;
	}

	virtual void handle_mouse()
	{

	}
};

#endif
