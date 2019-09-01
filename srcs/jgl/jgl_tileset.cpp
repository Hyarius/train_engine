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
	viewport->viewport();
	SDL_Rect dest = {pos.x, pos.y, size.x, size.y};
	SDL_Rect src = {sprites[id].x, sprites[id].y, sprites[id].x + unit.x, sprites[id].y + unit.y};
	SDL_RenderCopyEx(viewport->renderer(), image.texture(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}
