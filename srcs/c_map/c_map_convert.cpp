#include "engine.h"

Vector2 c_map::convert_to_map_coord(Vector2 source)
{
	return (((source - _viewport->anchor()) - (_map_anchor + size() / 2.0f)) / _zoom);
}

Vector2 c_map::convert_to_screen_coord(Vector2 source)
{
	return (map_anchor() + size() / 2 + source * zoom());
}
