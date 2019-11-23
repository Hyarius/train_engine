#ifndef JGL_TILESET_H
#define JGL_TILESET_H

#include "jgl_includes.h"
#include "jgl_image.h"

using namespace std;

class c_tileset
{
private:
	c_image image;
	Vector2 size;
	Vector2 unit;
	vector<Vector2> sprites;

public:
	c_tileset(string path, Vector2 p_size = Vector2(0, 0));
	void draw(int id, Vector2 pos, Vector2 size, c_viewport *viewport = nullptr);
};

#endif
