#include "engine.h"

c_journey::c_journey()
{
	_path.clear();
}

c_journey::~c_journey()
{
	for (size_t i = 0; i < _path.size(); i++)
		_path[i]->set_linked(false);

	for (size_t i = 0; i < _hour_panel.size(); i++)
	{
		if (_hour_panel[i] != nullptr)
			delete _hour_panel[i];
	}
	for (size_t i = 0; i < _wait_panel.size(); i++)
	{
		if (_wait_panel[i] != nullptr)
			delete _wait_panel[i];
	}
}

size_t c_journey::get_index(c_milestone *target)
{
	auto it = find(_path.begin(), _path.end(), target);
	size_t i = it - _path.begin();

	return (i);
}

void c_journey::add_point(c_milestone *new_point, pair_int p_hour, int p_wait_time)
{
	static Vector2 panel_size = Vector2(150, 30);
	static Vector2 delta = Vector2(-panel_size.x / 2, 20.0f);
	static Vector2 delta2 = Vector2(-panel_size.x / 2, 55.0f);
	_path.push_back(new_point);
	new_point->set_linked(true);

	c_hour_entry *new_hour = nullptr;
	c_frame *new_wait_frame = nullptr;
	c_value_entry *new_wait_entry = nullptr;
	c_text_label *new_wait_label = nullptr;

	if (new_point != nullptr && new_point->place() != nullptr)
	{
		new_hour = new c_hour_entry(p_hour.first, p_hour.second, g_map);
		new_hour->set_geometry(Vector2(g_map->convert_to_screen_coord(new_point->pos()) + delta), panel_size);
		new_hour->active();

		new_wait_frame = new c_frame(g_map);
		new_wait_frame->set_geometry(Vector2(g_map->convert_to_screen_coord(new_point->pos()) + delta2), panel_size);
		new_wait_frame->active();

		int border = new_wait_frame->box().border();

		Vector2 label_pos = 0;
		Vector2 label_size = panel_size - Vector2(panel_size.y, 0.0f) - 2 * border;

		new_wait_label = new c_text_label("Time in station : ", new_wait_frame);
		new_wait_label->box().set_border(0);
		new_wait_label->set_geometry(label_pos, label_size);
		new_wait_label->active();

		Vector2 entry_pos = label_pos + Vector2(label_size.x, 0.0f);
		Vector2 entry_size = Vector2(panel_size.x - label_size.x, panel_size.y) - 2 * border;

		new_wait_entry = new c_value_entry(p_wait_time, new_wait_frame);
		new_wait_entry->entry().set_precision(0);
		new_wait_entry->box().set_border(0);
		new_wait_entry->box().set_front(Color(0, 0, 0, 0));
		new_wait_entry->box().set_back(Color(0, 0, 0, 0));
		new_wait_entry->set_geometry(entry_pos, entry_size);
		new_wait_entry->active();
	}

	_hour_panel.push_back(new_hour);
	_wait_panel.push_back(new_wait_frame);
	_wait_label.push_back(new_wait_label);
	_wait_entry.push_back(new_wait_entry);
}

void c_journey::remove_point()
{
	_path.back()->set_linked(false);
	_path.pop_back();

	if (_hour_panel.back() != nullptr)
	{
		delete _hour_panel.back();
		delete _wait_panel.back();
		delete _wait_label.back();
		delete _wait_entry.back();
	}

	_hour_panel.pop_back();
}

void c_journey::actualize_panel()
{
	static Vector2 panel_size = Vector2(150, 30);
	static Vector2 delta = Vector2(-panel_size.x / 2, 20.0f);
	static Vector2 delta2 = Vector2(-panel_size.x / 2, 55.0f);

	for (size_t i = 0; i < _hour_panel.size(); i++)
	{
		if (_hour_panel[i] != nullptr)
			_hour_panel[i]->set_geometry(Vector2(g_map->convert_to_screen_coord(_path[i]->pos()) + delta), panel_size);
		if (_wait_panel[i] != nullptr)
		{
			int border = _wait_panel[i]->box().border();

			Vector2 label_pos = 0;
			Vector2 label_size = panel_size - Vector2(panel_size.y, 0.0f) - 2 * border;

			Vector2 entry_pos = label_pos + Vector2(label_size.x, 0.0f);
			Vector2 entry_size = Vector2(panel_size.x - label_size.x, panel_size.y) - 2 * border;

			_wait_panel[i]->set_geometry(Vector2(g_map->convert_to_screen_coord(_path[i]->pos()) + delta2), panel_size);
			_wait_label[i]->set_geometry(label_pos, label_size);
			_wait_entry[i]->set_geometry(entry_pos, entry_size);
		}
	}
}

void c_journey::draw()
{
	if (_path.size() <= 1)
		return;

	for (size_t i = 0; i < _path.size() - 1; i++)
	{
		Vector2 pos1 = g_map->convert_to_screen_coord(_path[i]->pos());
		Vector2 pos2 = g_map->convert_to_screen_coord(_path[i + 1]->pos());

		draw_line(g_map->viewport(), Color(255, 120, 0), pos1, pos2, 9);
	}
}

c_rail *c_journey::get_rail(c_map *map, size_t start_index)
{
	c_rail *result;
	pair_milestone key;

	if (start_index >= _path.size() - 1)
		return (nullptr);
	key = pair_milestone(_path[start_index], _path[start_index + 1]);
	result = map->rails()[key];

	if (result == nullptr)
		error_exit(1, "No rail found");

	if (result->distance() == -1)
		result->calc_distance(map->scale_unit());

	return (result);
}

string c_journey::name()
{
	string first;
	string second;
	string hour;

	first = (_path.front()->place() == nullptr ? "" : _path.front()->place()->name());
	second = (_path.back()->place() == nullptr ? "" : _path.back()->place()->name());
	hour = (_hour_panel.front() == nullptr ? "" : convert_hour_to_string(_hour_panel.front()->hour().value(), _hour_panel.front()->minute().value()));

	return ("[" + hour + "]-" + first + "-" + second);
}

void c_journey::calc_distance(c_map *map)
{
	c_rail *result;
	pair_milestone key;

	for (size_t i = 0; i < _path.size() - 1; i++)
	{
		key = pair_milestone(_path[i], _path[i + 1]);
		result = map->rails()[key];

		result->calc_distance(map->scale_unit());
	}
}
