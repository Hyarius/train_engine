#include "jgl.h"

using namespace std;

void draw_line(c_viewport *viewport, c_color c_color, Vector2 p1, Vector2 p2)
{
	viewport->viewport();
	viewport->set_c_color(c_color);

	SDL_RenderDrawLine(viewport->renderer(),
			static_cast<int>(p1.x), static_cast<int>(p1.y),
			static_cast<int>(p2.x), static_cast<int>(p2.y));
}

void draw_polygon(c_viewport *viewport, c_color c_color, vector<Vector2> points)
{
	viewport->set_c_color(c_color);

	for (size_t i = 0; i < points.size() - 1; i++)
	{
		draw_line(viewport, c_color, points[i], points[i + 1]);
	}
}

void draw_rectangle(c_viewport *viewport, c_color c_color, Vector2 pos, Vector2 size)
{
	viewport->viewport();
	viewport->set_c_color(c_color);

	SDL_Rect rect = {pos.x, pos.y, size.x, size.y};
	SDL_RenderDrawRect(viewport->renderer(), &rect);
}

void fill_rectangle(c_viewport *viewport, c_color c_color, Vector2 pos, Vector2 size)
{
	viewport->viewport();
	viewport->set_c_color(c_color);

	SDL_Rect rect = {pos.x, pos.y, size.x, size.y};
	SDL_RenderFillRect(viewport->renderer(), &rect);
}
