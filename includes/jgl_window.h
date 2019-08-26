#ifndef JGL_WINDOW_H
#define JGL_WINDOW_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_shader.h"

class Window
{
private:
	SDL_Window *_window;
	SDL_GLContext _context;
	Vector2 _win_size;
	Color _background_color;

	//Opengl info
	GLuint program_color;
	GLuint program_sprite;

public:
	Window(string name, Vector2 p_size = Vector2(), Color p_color = Color())
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

		_win_size = p_size;
		if (_win_size == Vector2())
		{
			SDL_DisplayMode current;
			SDL_GetDesktopDisplayMode(0, &current);
			_win_size = Vector2(current.w * 0.8f, current.h * 0.8f);
		}

		_window = SDL_CreateWindow(name.c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			static_cast<int>(_win_size.x), static_cast<int>(_win_size.y),
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		_context = SDL_GL_CreateContext(_window);

		glewInit();

		_background_color = p_color;

		program_color = load_shaders("ressources/shader/color_shader.vert", "ressources/shader/color_shader.frag");
		program_sprite = load_shaders("ressources/shader/texture_shader.vert", "ressources/shader/texture_shader.frag");

		clear();
		render();
	}

	~Window()
	{
		SDL_DestroyWindow(_window);
	}

	void clear()
	{
		glClearColor(_background_color.r, _background_color.g, _background_color.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void render()
	{
		SDL_GL_SwapWindow(_window);
	}
};


#endif