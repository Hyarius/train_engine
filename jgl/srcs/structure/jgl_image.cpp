#include "jgl.h"

c_image::c_image() : _surface(nullptr), _texture(nullptr) {}

c_image::c_image(string path)
{
	_surface = IMG_Load(path.c_str());

	if (_surface == nullptr)
		get_sdl_error();

	_texture = SDL_CreateTextureFromSurface(g_application->renderer(), _surface);

	if (_texture == nullptr)
		get_sdl_error();

	_size = Vector2(_surface->w, _surface->h);
}

c_image::c_image(size_t width, size_t height, Color p_color)
{
	SDL_Surface		*_surface;
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

    _surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(_surface, NULL, SDL_MapRGBA(_surface->format,
		(Uint8)(p_color.r * 255), (Uint8)(p_color.g * 255),
		(Uint8)(p_color.b * 255), (Uint8)(p_color.a * 255)));

	if (_surface == nullptr)
		get_sdl_error();

	_texture = SDL_CreateTextureFromSurface(g_application->renderer(), _surface);
	if (_texture == nullptr)
		get_sdl_error();

	_size = Vector2(_surface->w, _surface->h);
}

c_image::c_image(SDL_Surface *p__surface)
{
	_surface = p__surface;
	if (_surface == nullptr)
		error_exit(1, "Surface send in c_image = NUL");

	_texture = SDL_CreateTextureFromSurface(g_application->renderer(), _surface);
	if (_texture == nullptr)
		get_sdl_error();

	_size = Vector2(_surface->w, _surface->h);
}

void c_image::active()
{
	SDL_SetRenderTarget(g_application->renderer(), _texture);
}

void c_image::unactive()
{
	SDL_SetRenderTarget(g_application->renderer(), NULL);
}

void c_image::save(string file_path)
{
	SDL_Texture* target = SDL_GetRenderTarget(g_application->renderer());
    SDL_SetRenderTarget(g_application->renderer(), _texture);
    int width, height;
    SDL_QueryTexture(_texture, NULL, NULL, &width, &height);
    SDL_Surface* tmp_surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 255);
    SDL_RenderReadPixels(g_application->renderer(), NULL, tmp_surface->format->format, tmp_surface->pixels, tmp_surface->pitch);
    IMG_SavePNG(tmp_surface, file_path.c_str());
    SDL_FreeSurface(tmp_surface);
    SDL_SetRenderTarget(g_application->renderer(), target);
}

void c_image::draw(c_viewport *viewport, Vector2 pos, Vector2 size)
{
	SDL_Rect dest = {
			static_cast<int>(pos.x), static_cast<int>(pos.y),
			static_cast<int>(size.x), static_cast<int>(size.y)
		};
	SDL_RenderCopyEx(viewport->renderer(), _texture, NULL, &dest, 0, NULL, SDL_FLIP_NONE);
}

SDL_Surface *c_image::surface(){ return (_surface); }

SDL_Texture	*c_image::texture(){ return (_texture); }

Vector2 &c_image::size(){ return (_size); }
