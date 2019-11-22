#include "jgl.h"

using namespace std;

vector<Vector2> calc_point(int width)
{
	vector<Vector2> result;
	Vector2 center = 0;
	Vector2 actual;

	for (actual.x = -width / 2; actual.x <= width / 2 || actual.x == 0; actual.x++)
	{
		for (actual.y = -width / 2; actual.y <= width / 2 || actual.y == 0; actual.y++)
		{
			if (center.distance(actual) < width)
				result.push_back(actual);
		}
	}

	return (result);
}

void draw_line(c_viewport *viewport, Color p_color, Vector2 p1, Vector2 p2, int width)
{
	viewport->set_Color(p_color);

	vector<Vector2> to_draw = calc_point(width);
	Vector2 actual;

	for (size_t i = 0; i < to_draw.size(); i++)
	{
		SDL_RenderDrawLine(viewport->renderer(),
			to_draw[i].x + p1.x, to_draw[i].y + p1.y,
			to_draw[i].x + p2.x, to_draw[i].y + p2.y);
	}

}

void draw_point(c_viewport *viewport, Color p_color, Vector2 center, int width)
{
	viewport->set_Color(p_color);

	Vector2 actual;

	for (int i = -width / 2; i <= width / 2 || i == 0; i++)
	{
		for (int j = -width / 2; j <= width / 2 || j == 0; j++)
		{
			actual = center + Vector2(i, j);

			if (center.distance(actual) < width)
				SDL_RenderDrawPoint(viewport->renderer(), actual.x, actual.y);
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
