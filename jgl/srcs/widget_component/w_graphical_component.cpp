#include "jgl.h"


w_graphical_component::w_graphical_component(c_widget *p_owner) : w_component(p_owner)
{
	_border = 3;
	_back = Color(150, 150, 150, 255);
	_front = Color(195, 195, 195, 255);
}
