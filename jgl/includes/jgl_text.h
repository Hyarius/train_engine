#ifndef JGL_TEXT_DEFINE_H
#define JGL_TEXT_DEFINE_H

#include "jgl_includes.h"
#include "jgl_image.h"

#define FONT_PATH "ressources/font/Tinos-Regular.ttf"

#define NB_SIZE			150
#define NB_COLOR		26

#define BLACK			0
#define WHITE			1
#define LIGHT_BLUE		2
#define BLUE			3
#define DARK_BLUE		4
#define LIGHT_RED		5
#define RED				6
#define DARK_RED		7
#define LIGHT_GREEN		8
#define GREEN			9
#define DARK_GREEN		10
#define LIGHT_CYAN		11
#define CYAN			12
#define DARK_CYAN		13
#define LIGHT_GREY		14
#define GREY			15
#define DARK_GREY		16
#define LIGHT_ORANGE	17
#define ORANGE			18
#define DARK_ORANGE		19
#define LIGHT_YELLOW	20
#define YELLOW			21
#define DARK_YELLOW		22
#define LIGHT_PURPLE	23
#define PURPLE			24
#define DARK_PURPLE		25

#define NORMAL TTF_STYLE_NORMAL
#define BOLD TTF_STYLE_BOLD
#define ITALIC TTF_STYLE_ITALIC
#define UNDERLINE TTF_STYLE_UNDERLINE
#define STRICK TTF_STYLE_STRIKETHROUGH

SDL_Color get_color(int i);
TTF_Font *get_font(int size);
c_image	*get_char(char c, int size = 16, int p_color = 0, int type = NORMAL);
int draw_text(c_viewport *port, string text, Vector2 coord, int text_size = 16, int color_type = BLACK, int type = NORMAL);
int draw_centred_text(c_viewport *port, string text, Vector2 coord, int text_size = 16, int color_type = BLACK, int type = NORMAL);
int calc_text_len(string text, int text_size = 16);
int	max_char_in_box(int space, int size = 16);

#endif
