#ifndef JGL_WIDGET_COMPONENT_H
#define JGL_WIDGET_COMPONENT_H

class w_text_component
{
protected:
	string _text;
	int _text_size;
	int _text_color;
	int _text_style;

public:
	w_text_component(string p_text = "", int p_text_size = 16, int p_text_color = BLACK, int p_text_style = NORMAL);

	void calc_text_size(Vector2 p_area);

	void set_text(string p_text, Vector2 p_area);
	void set_color(int p_color = BLACK);
	void set_style(int p_style = NORMAL);

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

	void render(c_viewport *viewport, Vector2 pos, Vector2 size);
};

class w_box_component
{
protected:
	int _border_size;
	Color _front;
	Color _back;

public:
	w_box_component(int p_border_size = 0,
			Color p_back = Color(120, 120, 120),
			Color p_front = Color(165, 165, 165));

	void set_color(
		Color p_back = Color(120, 120, 120),
		Color p_front = Color(165, 165, 165));

	void set_border_size(int p_border_size = 0);

	void render(c_viewport *viewport, Vector2 pos, Vector2 size);
};

class w_entry_component
{
protected:
	bool selected;
	string text;
	int cursor;

	Uint32 next_input;
	Uint32 input_delay;

public:
	w_entry_component();

	void select();
	void unselect();

	void move_cursor(int delta);
	void add_text(string new_part);
	void remove_text();

	virtual void render();
}

#endif
