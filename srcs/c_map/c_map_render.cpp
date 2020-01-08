#include "engine.h"

#define LANDMARK_SIZE 2

void c_map::render()
{
	// cout << "Nb event : " << _city_nb_event_entry.size() << endl;
	_map->draw(_map_anchor + area() / 2.0f, _map->size() * _zoom, _viewport);

	if (_landmark1 != Vector2())
		fill_centred_rectangle(Color(0, 255, 0), convert_to_screen_coord(_landmark1), LANDMARK_SIZE * _zoom, _viewport);
	if (_landmark2 != Vector2())
		fill_centred_rectangle(Color(0, 255, 0), convert_to_screen_coord(_landmark2), LANDMARK_SIZE * _zoom, _viewport);

	for (size_t i = 0; i < _milestones.size(); i++)
		_milestones[i]->draw();

	for (size_t i = 0; i < _milestones.size(); i++)
		_milestones[i]->draw_link();

	if (_journey != nullptr)
		_journey->draw();

	for (size_t i = 0; i < _cities.size(); i++)
		_cities[i]->draw();
}
