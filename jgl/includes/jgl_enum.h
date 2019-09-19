#ifndef JGL_ENUM_H
#define JGL_ENUM_H

enum alignment
{
	left = 0,
	centred = 1,
	right = 2
};

enum text_color
{
	black = 0,
	white = 1,
	light_blue = 2,
	blue = 3,
	dark_blue = 4,
	light_red = 5,
	red = 6,
	dark_red = 7,
	light_green = 8,
	green = 9,
	dark_green = 10,
	light_cyan = 11,
	cyan = 12,
	dark_cyan = 13,
	light_grey = 14,
	grey = 15,
	Dark_grey = 16,
	light_orange = 17,
	orange = 18,
	dark_orange = 19,
	light_yellow = 20,
	yellow = 21,
	dark_yellow = 22,
	light_purple = 23,
	purple = 24,
	dark_purple = 25
};

enum text_style
{
	normal = TTF_STYLE_NORMAL,
	bold = TTF_STYLE_BOLD,
	italic = TTF_STYLE_ITALIC,
	underline = TTF_STYLE_UNDERLINE,
	strike = TTF_STYLE_STRIKETHROUGH
};

#endif
