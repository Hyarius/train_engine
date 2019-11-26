#include "jgl_includes.h"

struct Plot_data
{
	string name;
	string (*funct)(float);
	float min;
	float max;
	size_t precision;
	float delta;

	Plot_data(string p_name = "Value", float p_min = 0.0f, float p_max = 100.0f, string (*p_funct)(float) = nullptr)
	{
		name = p_name;
		funct = p_funct;
		min = p_min;
		max = p_max;
		precision = 0;
		delta = (max - min) / 10;
	}
	~Plot_data()
	{

	}
	void set_min(float p_min){min = p_min;delta = (max - min) / 10;}
	void set_max(float p_max){max = p_max;delta = (max - min) / 10;}
	void set_funct(string (*p_funct)(float)){funct = p_funct;}
	void divide(size_t nb_division){delta = (max - min) / nb_division;}
	void set_gap(float p_delta){delta = p_delta;}
	float range(){return (max - min);}
};

struct Line
{
	vector<Vector2> points;
	Color color;

	Line(Color p_color = Color(0, 0, 0))
	{
		points.clear();
		color = p_color;
	}
	~Line()
	{

	}

	void add_point(Vector2 p_point){points.push_back(p_point);}
	void set_color(Color p_color){color = p_color;}
};

class c_plot
{
private:
	c_image *_plot;

	Color _color;
	Vector2 _size;
	Vector2 _margin;

	Vector2 _origin;
	Vector2 _pos_up;
	Vector2 _pos_right;

	size_t _point_size;
	size_t _line_size;

	vector<Line> _lines;

	int _text_size;

	Plot_data _absciss;
	Vector2 _absciss_unit;
	Plot_data _ordinate;
	Vector2 _ordinate_unit;

public:
	c_plot(Vector2 p_size = Vector2(1280, 1080), Plot_data p_absciss = Plot_data("Absciss"), Plot_data p_ordinate = Plot_data("Ordinate"));
	~c_plot();

	void initialize();
	void clear();
	void draw();
	void draw_plot_point(Vector2 point, Color color);
	void draw_plot_line(Vector2 point_a, Vector2 point_b, Color color);
	void draw_absciss();
	void draw_absciss_point(float value);
	void draw_ordinate();
	void draw_ordinate_point(float value);
	void save(string path);

	Plot_data &absciss(){return (_absciss);}
	Plot_data &ordinate(){return (_ordinate);}

	void actualize_point();
	void calc_axis_unit();

	void add_line(Color p_color = Color(0, 0, 0));
	void add_point(Vector2 p_point, size_t line = 0);
	void add_point(float p_a, float p_b, size_t line = 0){add_point(Vector2(p_a, p_b), line);}
	void set_line_color(size_t index, Color p_color);

	void set_point_size(size_t p_size){_point_size = p_size;}
	void set_line_size(size_t p_size){_line_size = p_size;}

	void set_size(Vector2 p_size){_size = p_size;actualize_point();}
	void set_margin(Vector2 p_margin){_margin = p_margin;actualize_point();}
	void set_color(Color p_color){_color = p_color;}

	void set_absciss(Plot_data p_absciss){_absciss = p_absciss;calc_axis_unit();}
	void set_ordinate(Plot_data p_ordinate){_ordinate = p_ordinate;calc_axis_unit();}

	void set_absciss_name(string p_name){absciss().name = p_name;}
	void set_absciss_funct(string (*p_funct)(float)){absciss().set_funct(p_funct);}
	void set_absciss_min(float p_min){absciss().set_min(p_min);calc_axis_unit();}
	void set_absciss_max(float p_max){absciss().set_max(p_max);calc_axis_unit();}
	void set_absciss_gap(float p_gap){absciss().set_gap(p_gap);calc_axis_unit();}
	void divide_absciss(size_t subdivision){absciss().divide(subdivision);calc_axis_unit();}
	void set_absciss_precision(int p_precision){absciss().precision = p_precision;}

	void set_ordinate_name(string p_name){ordinate().name = p_name;}
	void set_ordinate_funct(string (*p_funct)(float)){ordinate().set_funct(p_funct);}
	void set_ordinate_min(float p_min){ordinate().set_min(p_min);calc_axis_unit();}
	void set_ordinate_max(float p_max){ordinate().set_max(p_max);calc_axis_unit();}
	void set_ordinate_gap(float p_gap){ordinate().set_gap(p_gap);calc_axis_unit();}
	void divide_ordinate(size_t subdivision){ordinate().divide(subdivision);calc_axis_unit();}
	void set_ordinate_precision(int p_precision){ordinate().precision = p_precision;}

};
