#ifndef JGL_WIDGET_COMPONENT_H
#define JGL_WIDGET_COMPONENT_H

class w_text_component
{
protected:
	string _text;
	Vector2 _anchor;
	Vector2 _area;
	int _size;
	alignment _align;
	text_color _color;
	text_style _style;

public:
		//Constructor
	w_text_component(string p_text = "");

		//Destructor
	~w_text_component();

		//Setter
	void 		set_text(string p_text){_text = p_text;}
	void 		set_align(alignment p_align){_align = p_align;}
	void 		set_anchor(Vector2 p_anchor){_anchor = p_anchor;}
	void 		set_area(Vector2 p_area){_area = p_area;}
	void 		set_size(int p_size){_size = p_size;}
	void 		set_color(text_color p_color){_color = p_color;}
	void 		set_style(text_style p_style){_style = p_style;}
	void 		calc_text_size();
	void 		resize(Vector2 p_anchor, Vector2 p_area){
		set_anchor(p_anchor);set_area(p_area);calc_text_size();
	}

		//Getter
	string 		text(){return (_text);}
	alignment 	align(){return (_align);}
	Vector2 	anchor(){return (_anchor);}
	Vector2 	area(){return (_area);}
	int 		size(){return (_size);}
	text_color 	color(){return (_color);}
	text_style 	style(){return (_style);}

	void render(c_viewport *viewport);

};

class w_check_component
{
protected:
	bool _state;
	Vector2 _anchor;
	Vector2 _area;
	Color _back;
	Color _front;
	Color _check;
	int _border;

public:
		//Constructor
	w_check_component(bool p_state = false);

		//Destructor
	~w_check_component();

		//Setter
	void set_state(bool p_state){_state = p_state;}
	void set_anchor(Vector2 p_anchor){_anchor = p_anchor;}
	void set_area(Vector2 p_area){_area = p_area;}
	void set_border(int p_border){_border = p_border;}
	void set_back(Color p_back){_back = p_back;}
	void set_front(Color p_front){_front = p_front;}
	void set_check(Color p_check){_check = p_check;}

		//Getter
	bool state(){return (_state);}
	Vector2 anchor(){return (_anchor);}
	Vector2 area(){return (_area);}
	int border(){return (_border);}
	Color back(){return (_back);}
	Color front(){return (_front);}
	Color check(){return (_check);}

	bool check(Vector2 point, Vector2 viewport_anchor);

	void render(c_viewport *viewport);

};

class w_box_component
{
protected:
	Vector2 _anchor;
	Vector2 _area;
	Color _back;
	Color _front;
	int _border;

public:
		//Constructor
	w_box_component();

		//Destructor
	~w_box_component();

		//Setter
	void set_anchor(Vector2 p_anchor){_anchor = p_anchor;}
	void set_area(Vector2 p_area){_area = p_area;}
	void set_border(int p_border){_border = p_border;}
	void set_back(Color p_back){_back = p_back;}
	void set_front(Color p_front){_front = p_front;}

		//Getter
	Vector2 anchor(){return (_anchor);}
	Vector2 area(){return (_area);}
	int border(){return (_border);}
	Color back(){return (_back);}
	Color front(){return (_front);}

	void render(c_viewport *viewport, Color delta = Color(255, 255, 255, 0));
};

class w_text_entry_component
{
protected:
	string _text;
	int _cursor;

	string _text_to_draw;
	int _cursor_to_draw;

	Vector2 _anchor;
	Vector2 _area;
	int _size;
	alignment _align;
	text_color _color;
	text_style _style;

public:
		//Constructor
	w_text_entry_component(string p_text = "");

		//Destructor
	~w_text_entry_component();

		//Setter
	void 		set_text(string p_text){_text = p_text;}
	void 		set_align(alignment p_align){_align = p_align;}
	void 		set_anchor(Vector2 p_anchor){_anchor = p_anchor;}
	void 		set_area(Vector2 p_area){_area = p_area;}
	void 		set_size(int p_size){_size = p_size;}
	void 		set_color(text_color p_color){_color = p_color;}
	void 		set_style(text_style p_style){_style = p_style;}
	void 		resize(Vector2 p_anchor, Vector2 p_area)
		{set_anchor(p_anchor);set_area(p_area);calc_text_size();}

		//Getter
	string 		text(){return (_text);}
	int 		cursor(){return (_cursor);}
	string 		text_to_draw(){return (_text_to_draw);}
	int 		cursor_to_draw(){return (_cursor_to_draw);}
	alignment 	align(){return (_align);}
	Vector2 	anchor(){return (_anchor);}
	Vector2 	area(){return (_area);}
	int 		size(){return (_size);}
	text_color 	color(){return (_color);}
	text_style 	style(){return (_style);}

	void 		calc_text_size();
	void 		calc_text_to_draw();
	void 		move_cursor(int delta);
	void 		add_text(string new_text);
	void 		remove_text();

	void 		render(c_viewport *viewport);
};

class w_value_component
{
protected:
	float _value;
	string _text;
	Vector2 _anchor;
	Vector2 _area;
	int _size;
	alignment _align;
	text_color _color;
	text_style _style;

public:
		//Constructor
	w_value_component(float p_value = 0.0f);

		//Destructor
	~w_value_component();

		//Setter
	void 		set_value(float p_value){_value = p_value;_text = ftoa(_value);};
	void 		set_align(alignment p_align){_align = p_align;}
	void 		set_anchor(Vector2 p_anchor){_anchor = p_anchor;}
	void 		set_area(Vector2 p_area){_area = p_area;}
	void 		set_size(int p_size){_size = p_size;}
	void 		set_color(text_color p_color){_color = p_color;}
	void 		set_style(text_style p_style){_style = p_style;}
	void 		resize(Vector2 p_anchor, Vector2 p_area)
		{set_anchor(p_anchor);set_area(p_area);calc_text_size();}

		//Getter
	float		value(){return (_value);}
	string 		text(){return (_text);}
	alignment 	align(){return (_align);}
	Vector2 	anchor(){return (_anchor);}
	Vector2 	area(){return (_area);}
	int 		size(){return (_size);}
	text_color 	color(){return (_color);}
	text_style 	style(){return (_style);}

	void 		calc_text_size();

	void render(c_viewport *viewport);
};

class w_value_entry_component
{
protected:
	float _value;
	string _text;
	int _cursor;

	string _text_to_draw;
	int _cursor_to_draw;

	Vector2 _anchor;
	Vector2 _area;
	int _size;
	alignment _align;
	text_color _color;
	text_style _style;

public:
		//Constructor
	w_value_entry_component(float p_value = 0.0f);

		//Destructor
	~w_value_entry_component();

		//Setter
	void 		set_text(string p_text){_text = p_text;calc_value();}
	void 		set_value(float p_value){_value = p_value;calc_text();}
	void 		set_align(alignment p_align){_align = p_align;}
	void 		set_anchor(Vector2 p_anchor){_anchor = p_anchor;}
	void 		set_area(Vector2 p_area){_area = p_area;}
	void 		set_size(int p_size){_size = p_size;}
	void 		set_color(text_color p_color){_color = p_color;}
	void 		set_style(text_style p_style){_style = p_style;}
	void 		resize(Vector2 p_anchor, Vector2 p_area)
		{set_anchor(p_anchor);set_area(p_area);calc_text_size();}
	void 		calc_value(){ _value = atof(_text.c_str());}
	void 		calc_text(){ _text = ftoa(_value);}

		//Getter
	string 		text(){return (_text);}
	float 		value(){return (_value);}
	int 		cursor(){return (_cursor);}
	string 		text_to_draw(){return (_text_to_draw);}
	int 		cursor_to_draw(){return (_cursor_to_draw);}
	alignment 	align(){return (_align);}
	Vector2 	anchor(){return (_anchor);}
	Vector2 	area(){return (_area);}
	int 		size(){return (_size);}
	text_color 	color(){return (_color);}
	text_style 	style(){return (_style);}

	void 		calc_text_size();
	void 		calc_text_to_draw();
	void 		move_cursor(int delta);
	void 		add_text(string new_text);
	void 		remove_text();

	void render(c_viewport *viewport);
};

#endif
