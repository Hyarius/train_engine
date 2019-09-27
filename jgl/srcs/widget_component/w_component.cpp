#include "jgl.h"

w_component::w_component(class c_widget *p_owner)
{
	_owner = p_owner;
	_anchor = Vector2() + owner_anchor();
	_area = Vector2();
}

Vector2		w_component::owner_anchor()
{
	Vector2 result = Vector2(0, 0);
	class c_widget *tmp;

	tmp = _owner;

	if (tmp == nullptr || tmp->parent() == nullptr)
		return (result);

	tmp = tmp->parent();

	result = result + tmp->viewport()->anchor();

	return (result);
};
