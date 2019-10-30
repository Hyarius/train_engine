#include "engine.h"

void c_map::remove_path(c_milestone *target)
{
	for (size_t i = _journey->path().size() - 1; _journey->path()[i] != target; i--)
		_journey->remove_point();
}
