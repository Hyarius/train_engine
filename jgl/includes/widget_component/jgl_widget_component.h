#ifndef JGL_WIDGET_COMPONENT_H
#define JGL_WIDGET_COMPONENT_H

class w_text_component
{
protected:
	alignment _align;
	string _text;
	int _text_size;
	int _text_color;
	int _text_style;

public:
	w_text_component(string p_text = "", int p_text_size = 16, int p_text_color = BLACK, int p_text_style = NORMAL, alignment p_allign = alignment::left);

	void calc_text_size(Vector2 p_area);

	void set_text(string p_text, int p_text_size = -1);
	void set_text(string p_text, Vector2 p_area = -1);
	void set_size(int p_text_size);
	void set_color(int p_color);
	void set_style(int p_style);
	void set_alignment(alignment p_align);

	int text_size();
	alignment align();

	void render(c_viewport *viewport, Vector2 pos);
};

class w_check_component
{
protected:
	bool _state;

public:
	w_check_component();

	bool state();
	void set_state(bool p_state);
	bool check(Vector2 point, Vector2 pos1, Vector2 pos2);

	void render(c_viewport *viewport, Vector2 pos, Vector2 size);
};

class w_box_component
{
protected:
	int _border_size;
	Color _front;
	Color _back;

public:
	w_box_component(int p_border_size = 3,
			Color p_back = Color(120, 120, 120),
			Color p_front = Color(165, 165, 165));

	int border_size();

	void set_color(Color p_back, Color p_front);

	void set_back(Color p_back);

	void set_front(Color p_front);

	void set_border_size(int p_border_size = 0);

	void render(c_viewport *viewport, Vector2 pos, Vector2 size, Color delta = Color(0, 0, 0, 0));
};

class w_entry_component
{
protected:
	bool _selected;
	string _text;
	int _cursor;

public:
	w_entry_component();

	int cursor();
	string text();
	bool selected();

	void select();
	void unselect();

	void move_cursor(int delta);
	void add_text(string new_text);
	void remove_text();

	void render(c_viewport *viewport, Vector2 area, int text_size = 16, int delta = 3);
};

class w_value_component
{
protected:
	alignment _align;
	float _value;
	string _text;
	int _text_size;
	int _text_color;
	int _text_style;

public:
	w_value_component(float p_value = 0.0f, int p_text_size = 16, int p_text_color = BLACK, int p_text_style = NORMAL, alignment p_allign = alignment::left);

	void calc_text_size(Vector2 p_area);

	void set_value(float value, Vector2 area = -1);
	void set_value(float value, int p_text_size = -1);
	void set_size(int p_text_size);
	void set_color(int p_color);
	void set_style(int p_style);
	void set_alignment(alignment p_align);

	int text_size();
	alignment align();

	void render(c_viewport *viewport, Vector2 pos);
};

#endif
