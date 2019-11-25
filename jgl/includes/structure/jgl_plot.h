#include "jgl_includes.h"

struct Plot_data
{
	string name;
	float min;
	float max;
	size_t precision;
	float delta;

	Plot_data(string p_name = "Value", float p_min = 0.0f, float p_max = 100.0f)
	{
		name = p_name;
		min = p_min;
		max = p_max;
		precision = 0;
		delta = (max - min) / 10;
	}
	void set_min(float p_min){min = p_min;delta = (max - min) / 10;}
	void set_max(float p_max){max = p_max;delta = (max - min) / 10;}
	void divide(size_t nb_division){delta = (max - min) / nb_division;}
	void set_gap(float p_delta){delta = p_delta;}
};

class c_plot
{
private:
	c_image *plot;

	Color color;
	Vector2 size;
	Vector2 margin;

	Vector2 origin;
	Vector2 pos_up;
	Vector2 pos_right;

	vector<Vector2> points;

	int text_size;

	Plot_data absciss;
	Vector2 absciss_unit;
	Plot_data ordinate;
	Vector2 ordinate_unit;

public:
	c_plot(Vector2 p_size = Vector2(1280, 1080), Plot_data p_absciss = Plot_data("Absciss"), Plot_data p_ordinate = Plot_data("Ordinate"));
	~c_plot();

	void initialize();
	void draw();
	void draw_plot_point(Vector2 point);
	void draw_plot_line(Vector2 point_a, Vector2 point_b);
	void draw_absciss();
	void draw_absciss_point(float value);
	void draw_ordinate();
	void draw_ordinate_point(float value);
	void save(string path);

	void actualize_point();
	void calc_axis_unit();

	void add_point(Vector2 p_point){points.push_back(p_point);}

	void set_size(Vector2 p_size){size = p_size;actualize_point();}
	void set_margin(Vector2 p_margin){margin = p_margin;actualize_point();}
	void set_color(Color p_color){color = p_color;}

	void set_absciss(Plot_data p_absciss){absciss = p_absciss;calc_axis_unit();}
	void set_ordinate(Plot_data p_ordinate){ordinate = p_ordinate;calc_axis_unit();}

	void set_absciss_name(string p_name){absciss.name = p_name;}
	void set_absciss_min(float p_min){absciss.set_min(p_min);calc_axis_unit();}
	void set_absciss_max(float p_max){absciss.set_max(p_max);calc_axis_unit();}
	void set_absciss_gap(float p_gap){absciss.set_gap(p_gap);calc_axis_unit();}
	void divide_absciss(size_t subdivision){absciss.divide(subdivision);calc_axis_unit();}
	void set_absciss_precision(int p_precision){absciss.precision = p_precision;}

	void set_ordinate_name(string p_name){ordinate.name = p_name;}
	void set_ordinate_min(float p_min){ordinate.set_min(p_min);calc_axis_unit();}
	void set_ordinate_max(float p_max){ordinate.set_max(p_max);calc_axis_unit();}
	void set_ordinate_gap(float p_gap){ordinate.set_gap(p_gap);calc_axis_unit();}
	void divide_ordinate(size_t subdivision){ordinate.divide(subdivision);calc_axis_unit();}
	void set_ordinate_precision(int p_precision){ordinate.precision = p_precision;}

};
