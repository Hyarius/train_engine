#include "jgl.h"

w_component::w_component(class c_widget *p_owner)
{
	_owner = p_owner;
	_anchor = Vector2() + owner_anchor();
	_area = Vector2();
}

Vector2		w_component::owner_anchor()
{
	if (_owner == nullptr || _owner->parent() == nullptr)
		return (Vector2(0, 0));

	return (_owner->parent()->anchor());
};


bool w_component::is_pointed(Vector2 point)
{
	c_widget *tmp;
	Vector2 pos1, pos2;

	pos1 = _anchor;

	pos2 = pos1 + _area;

	if (point.x < pos1.x || point.x > pos2.x || point.y < pos1.y || point.y > pos2.y)
		return (false);
	return (true);
}
