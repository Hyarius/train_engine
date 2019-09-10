#include "jgl.h"

using namespace std;

void draw_line(c_viewport *viewport, Color Color, Vector2 p1, Vector2 p2)
{
	viewport->set_Color(Color);

	SDL_RenderDrawLine(viewport->renderer(),
			static_cast<int>(p1.x), static_cast<int>(p1.y),
			static_cast<int>(p2.x), static_cast<int>(p2.y));
}

void draw_polygon(c_viewport *viewport, Color Color, vector<Vector2> points)
{
	viewport->set_Color(Color);

	for (size_t i = 0; i < points.size() - 1; i++)
	{
		draw_line(viewport, Color, points[i], points[i + 1]);
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
