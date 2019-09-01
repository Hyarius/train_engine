#include "jgl.h"

TTF_Font *font[NB_SIZE] = {
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr
};
c_image *char_list[NB_SIZE][NB_COLOR][5][256];
SDL_Color color_tab[NB_COLOR] = {
	{39, 39, 39, 255},
	{240, 240, 240, 255},
	{135, 206, 250, 255},
	{30, 144, 255, 255},
	{0, 0, 139, 255},
	{221, 110, 110, 255},
	{165, 89, 89, 255},
	{110, 70, 70, 255},
	{170, 220, 115, 255},
	{89, 165, 89, 255},
	{30, 100, 60, 255},
	{127, 255, 212, 255},
	{64, 224, 208, 255},
	{0, 139, 139, 255},
	{175, 175, 175, 255},
	{86, 86, 86, 255},
	{56, 56, 56, 255},
	{255, 195, 0, 255},
	{255, 165, 0, 255},
	{255, 130, 0, 255},
	{255, 250, 205, 255},
	{255, 228, 181, 255},
	{255, 255, 0, 255},
	{186, 85, 211, 255},
	{138, 43, 226, 255},
	{130, 0, 130, 255}
};

SDL_Color			get_color(int i)
{
	if (i < 0 || i >= NB_COLOR)
		return (color_tab[0]);
	return (color_tab[i]);
}

TTF_Font *get_font(int size)
{
	if (size < 0 || size > 30)
		error_exit(1, "Invalid size");


	if (font[size] == nullptr)
	{
		font[size] = TTF_OpenFont(FONT_PATH, size);
		if (font[size] == NULL)
			error_exit(1, "Can't load a font");
	}


	return (font[size]);
}

c_image				*get_char(char c, int size, int p_color, int type)
{
	if (char_list[type][size][p_color][c] == NULL)
	{
		TTF_Font *tmp = get_font(size);

		TTF_SetFontStyle(tmp, type);

		string text = " ";
		text[0] = c;
		char_list[size][p_color][type][c] = new c_image(TTF_RenderText_Blended(tmp, text.c_str(), get_color(p_color)));
		TTF_SetFontStyle(font[size], NORMAL);
	}
	return (char_list[size][p_color][type][c]);
}

int				draw_text(c_viewport *port, string text, Vector2 coord, int text_size, int color_type, int type)
{
	c_image			*image;
	size_t			i = 0;
	Vector2			rel_coord;
	int				delta = 0;

	while (i < text.length())
	{
		rel_coord = Vector2(coord.x + delta, coord.y);
		image = get_char( text[i], text_size, color_type, type);
		image->draw(port, rel_coord, image->size());
		delta += image->size().x;
		i++;
	}
	return (delta);
}
