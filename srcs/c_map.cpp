#include "engine.h"

c_map::c_map(string path, c_widget *parent) : c_widget(parent)
{
	map = c_image(path);
	anchor = map.size() / 2;
	zoom = 1;
}

void c_map::render()
{
	_viewport->clear();

	map.draw(_viewport, anchor * zoom - map.size() * zoom, map.size() * zoom);

	for (size_t i = 0; i < _childrens.size(); i++)
		_childrens[i]->render();
}

void c_map::handle_keyboard()
{
	if (keyboard->get_key(SDL_SCANCODE_E) == true)
		cout << "Key E pressed" << endl;
	if (keyboard->get_key(SDL_SCANCODE_W) == true)
		cout << "Key W pressed" << endl;
	if (keyboard->get_key(SDL_SCANCODE_Q) == true)
		cout << "Key Q pressed" << endl;
	if (keyboard->get_key(SDL_SCANCODE_R) == true)
		cout << "Key R pressed" << endl;
}

void c_map::handle_mouse()
{
	if (mouse->get_button(MOUSE_LEFT) == true)
	{
		if (mouse->rel_pos != Vector2())
			anchor = anchor + mouse->rel_pos;
	}
	if (mouse->wheel != 0)
	{
		if (mouse->wheel > 0)
			zoom *= 1.2f;
		else
			zoom *= 0.8f;
	}

}
