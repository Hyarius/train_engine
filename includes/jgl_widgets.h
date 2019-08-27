#ifndef JGL_WIDGETS_H
#define JGL_WIDGETS_H

#include "jgl_viewport.h"

using namespace std;

class jgl_widget
{
private:
	jgl_widget *_parent;
	vector<jgl_widget *> _childrens;
	c_viewport *viewport;

public:
	jgl_widget(jgl_widget *p_parent = NULL)
	{
		_childrens.clear();
		set_parent(p_parent);
		viewport = new c_viewport();
		set_background_color();
		set_geometry();
	}

	void set_background_color(c_color p_background = c_color(50, 50, 50))
	{
		viewport->set_background(p_background);
	}

	void set_geometry(Vector2 p_anchor = Vector2(0, 0), Vector2 p_size = Vector2(0, 0))
	{
		if (_parent == NULL)
			viewport->resize(p_anchor, p_size);
		else
		{
			if (p_anchor.x < 0)
			{
				p_size.x -= p_anchor.x;
			}

			Vector2 tmp_anchor = p_anchor + _parent->anchor();
			Vector2 tmp_size = p_size;

			// tmp_size.x = (p_anchor.x + p_size.x >= _parent->size().x ? _parent->size().x - p_anchor.x : p_size.x);
			// tmp_size.y = (p_anchor.y + p_size.y >= _parent->size().y ? _parent->size().y - p_anchor.y : p_size.y);

			viewport->resize(tmp_anchor, tmp_size);
		}
	}

	Vector2 size()
	{
		return (viewport->size());
	}

	Vector2 anchor()
	{
		return (viewport->anchor());
	}

	void set_parent(jgl_widget *p_parent)
	{
		_parent = p_parent;
		if (p_parent != NULL)
			p_parent->add_children(this);
	}

	void add_children(jgl_widget *p_children)
	{
		_childrens.push_back(p_children);
	}

	void render()
	{
		viewport->clear();

		for (size_t i = 0; i < _childrens.size(); i++)
			_childrens[i]->render();
	}
};

#endif
