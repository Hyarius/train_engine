#include "jgl.h"

vector<TTF_Font *>font = vector<TTF_Font *>();

vector <vector <vector <vector <c_image *> > > > char_list;
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
	if (size < 2)
		error_exit(1, "Can't load a font of size < 2");

	if (font.size() < size)
		font.resize(size + 1);

	if (font[size] == nullptr)
	{
		font[size] = TTF_OpenFont(FONT_PATH, size);
		if (font[size] == nullptr)
			error_exit(1, "Can't load a font");
	}


	return (font[size]);
}

c_image				*get_char(char c, int size, text_color color, text_style type)
{
	if (size <= 0)
		return (nullptr);

	int tmp_color = static_cast<int>(color);
	int tmp_type = static_cast<int>(type);

	if (char_list.size() <= tmp_type)
		char_list.resize(tmp_type + 1);
	if (char_list[tmp_type].size() <= (size_t)size)
		char_list[tmp_type].resize(size + 1);
	if (char_list[tmp_type][size].size() <= (size_t)tmp_color)
		char_list[tmp_type][size].resize(tmp_color + 1);
	if (char_list[tmp_type][size][tmp_color].size() <= (size_t)c)
		char_list[tmp_type][size][tmp_color].resize(c + 1);
	if (char_list[tmp_type][size][tmp_color][c] == nullptr)
	{
		TTF_Font *tmp = get_font(size);

		TTF_SetFontStyle(tmp, tmp_type);

		string text = " ";
		text[0] = c;

		typedef std::basic_string<Uint16, std::char_traits<Uint16>, std::allocator<Uint16> > u16string;
		u16string utext(text.begin(), text.end());

		char_list[tmp_type][size][tmp_color][c] = new c_image(TTF_RenderUNICODE_Blended(tmp, utext.c_str(), get_color(tmp_color)));
		TTF_SetFontStyle(font[size], static_cast<int>(text_style::normal));
	}
	return (char_list[tmp_type][size][tmp_color][c]);
}

int				draw_text(c_viewport *port, string text, Vector2 coord, int size, text_color color, text_style type)
{
	c_image			*image;
	size_t			i = 0;
	Vector2			rel_coord;
	int				delta = 0;

	if (size <= 2)
		return 0;

	while (i < text.length())
	{
		rel_coord = Vector2(coord.x + delta, coord.y);
		image = get_char(text[i], size, color, type);
		image->draw(port, rel_coord, image->size());
		delta += image->size().x;
		i++;
	}
	return (delta);
}

int				max_char_in_box(int space, int size)
{
	int nb_char = 0;
	int delta = 0;

	while (delta < space)
	{
		delta += get_char('M', size)->size().x;
		nb_char++;
	}

	return (nb_char);
}

int				calc_text_len(string text, int size)
{
	c_image			*image;
	size_t			i = 0;
	int				delta = 0;

	while (i < text.length())
	{
		image = get_char(text[i], size);
		delta += image->size().x;
		i++;
	}
	return (delta);
}

int				draw_centred_text(c_viewport *viewport, string text, Vector2 coord, int size, text_color color, text_style type)
{
	if (size <= 2)
		return 0;

	int x = calc_text_len(text, size);
	int y = get_char('M', size, color, type)->size().y;

	return (draw_text(viewport, text, Vector2(coord.x - x / 2, coord.y - y / 2), size, color, type));
}
