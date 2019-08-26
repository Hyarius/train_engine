#ifndef JGL_IMAGE_H
#define JGL_IMAGE_H

#include "jgl_includes.h"
#include "jgl_basics_functions.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_window.h"

class				c_image
{
private:
	SDL_Surface		*surface;
	SDL_Texture		*texture;

public:
	c_image() : surface(nullptr), texture(nullptr) {}

	c_image(string path)
	{
		surface = IMG_Load(path.c_str());
		if (surface == NULL)
			error_exit(1, "Can't load " + path + " file");

		texture = SDL_CreateTextureFromSurface(main_window->renderer(), surface);
		if (texture == nullptr)
			error_exit(1, "Error while creating the texture from " + path + " file");
	}

	c_image(c_color p_color)
	{
		SDL_Surface		*surface;
		Uint32			rmask, gmask, bmask, amask;

		#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		    rmask = 0xff000000;
		    gmask = 0x00ff0000;
		    bmask = 0x0000ff00;
		    amask = 0x000000ff;
		#else
		    rmask = 0x000000ff;
		    gmask = 0x0000ff00;
		    bmask = 0x00ff0000;
		    amask = 0xff000000;
		#endif

	    surface = SDL_CreateRGBSurface(0, 1, 1, 32, rmask, gmask, bmask, amask);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format,
			(Uint8)(p_color.r * 255), (Uint8)(p_color.g * 255),
			(Uint8)(p_color.b * 255), (Uint8)(p_color.a * 255)));

		if (surface == NULL)
			error_exit(1, "Can't create a surface of color " +
											to_string((int)(p_color.r * 255)) + "/" +
											to_string((int)(p_color.g * 255)) + "/" +
											to_string((int)(p_color.b * 255)) + "/" +
											to_string((int)(p_color.a * 255)));

		texture = SDL_CreateTextureFromSurface(main_window->renderer(), surface);
		if (texture == nullptr)
			error_exit(1, "Error while creating the texture for the color " +
											to_string((int)(p_color.r * 255)) + "/" +
											to_string((int)(p_color.g * 255)) + "/" +
											to_string((int)(p_color.b * 255)) + "/" +
											to_string((int)(p_color.a * 255)));

	}

	c_image(SDL_Surface *p_surface)
	{
		surface = p_surface;
		if (surface == nullptr)
			error_exit(1, "Surface send in c_image = NULL");

		texture = SDL_CreateTextureFromSurface(main_window->renderer(), surface);
		if (texture == nullptr)
			error_exit(1, "Error while creating the texture from a SDL_surface");
	}

	void draw(c_viewport *viewport, Vector2 pos, Vector2 size)
	{
		viewport->viewport();
		SDL_Rect dest = {pos.x, pos.y, size.x, size.y};
		SDL_RenderCopyEx(viewport->renderer(), texture, NULL, &dest, 0, NULL, SDL_FLIP_NONE);
	}

	Vector2 size()
	{
		return (Vector2(surface->w, surface->h));
	}

};

#endif
