#include "jgl.h"

using namespace std;

void draw_line(c_viewport *viewport, Color p_color, Vector2 p1, Vector2 p2, int width)
{
	Vector2 tmp_1;
	Vector2 tmp_2;
	Vector2 cross;

	cross = (p1.cross(p2)).normalize();

	viewport->set_Color(p_color);

	for (int i = 0; i <= width / 2 || i == 0; i++)
	{
		tmp_1 = p1 + cross * i;
		tmp_2 = p2 + cross * i;
		SDL_RenderDrawLine(viewport->renderer(),
				static_cast<int>(tmp_1.x), static_cast<int>(tmp_1.y),
				static_cast<int>(tmp_2.x), static_cast<int>(tmp_2.y));

		if (i != 0)
		{
			tmp_1 = p1 - cross * i;
			tmp_2 = p2 - cross * i;
			SDL_RenderDrawLine(viewport->renderer(),
					static_cast<int>(tmp_1.x), static_cast<int>(tmp_1.y),
					static_cast<int>(tmp_2.x), static_cast<int>(tmp_2.y));
		}
	}
}

void draw_rectangle(c_viewport *viewport, Color Color, Vector2 pos, Vector2 size)
{
	viewport->set_Color(Color);

	SDL_Rect rect = {
		static_cast<int>(pos.x), static_cast<int>(pos.y),
		static_cast<int>(size.x), static_cast<int>(size.y)};
	SDL_RenderDrawRect(viewport->renderer(), &rect);
}

void fill_rectangle(c_viewport *viewport, Color Color, Vector2 pos, Vector2 size)
{
	viewport->set_Color(Color);

	SDL_Rect rect = {
		static_cast<int>(pos.x), static_cast<int>(pos.y),
		static_cast<int>(size.x), static_cast<int>(size.y)};
	SDL_RenderFillRect(viewport->renderer(), &rect);
}

void draw_centred_rectangle(c_viewport *viewport, Color Color, Vector2 pos, Vector2 size)
{
	viewport->set_Color(Color);

	SDL_Rect rect = {
		static_cast<int>(pos.x - size.x / 2), static_cast<int>(pos.y - size.y / 2),
		static_cast<int>(size.x), static_cast<int>(size.y)};
	SDL_RenderDrawRect(viewport->renderer(), &rect);
}

void fill_centred_rectangle(c_viewport *viewport, Color Color, Vector2 pos, Vector2 size)
{
	viewport->set_Color(Color);

	SDL_Rect rect = {
		static_cast<int>(pos.x - size.x / 2), static_cast<int>(pos.y - size.y / 2),
		static_cast<int>(size.x), static_cast<int>(size.y)};
	SDL_RenderFillRect(viewport->renderer(), &rect);
}
