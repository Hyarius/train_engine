#include "jgl.h"

using namespace std;

c_tileset::c_tileset(string path, Vector2 p_size)
{
	image = c_image(path);
	size = p_size;
	unit = image.size() / size;
	Vector2	tmp = Vector2(0, 0);

	while (1)
	{
		sprites.push_back(tmp * unit);

		if (tmp == size - 1)
			break;
		if (tmp.x >= p_size.x - 1)
		{
			tmp.x = 0;
			tmp.y++;
		}
		else
			tmp.x++;
	}
}

void c_tileset::draw(c_viewport *viewport, int id, Vector2 pos, Vector2 size)
{
	SDL_Rect dest = {
			static_cast<int>(pos.x), static_cast<int>(pos.y),
			static_cast<int>(size.x), static_cast<int>(size.y)
		};
	SDL_Rect src = {
			static_cast<int>(sprites[id].x), static_cast<int>(sprites[id].y),
			static_cast<int>(unit.x), static_cast<int>(unit.y)};
	SDL_RenderCopyEx(viewport->renderer(), image.texture(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}
