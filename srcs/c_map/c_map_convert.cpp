#include "engine.h"

Vector2 c_map::convert_to_map_coord(Vector2 source)
{
	return (((source - _viewport->anchor()) - (_map_anchor + size() / 2.0f)) / _zoom);
}

Vector2 c_map::convert_to_screen_coord(Vector2 source)
{
	return (map_anchor() + size() / 2 + source * zoom());
}

void c_map::calc_distance_ratio()
{
	float distance = vector2_distance(_landmark1, _landmark2);
	float scale = _landmark_scale->entry().value();
	_scale_unit = 1.0f / (distance / (scale == 0 ? 1 : scale));
}

float c_map::milestone_distance(c_milestone *point_a, c_milestone *point_b)
{
	return (vector2_distance(point_a->pos(), point_b->pos()) * _scale_unit);
}
