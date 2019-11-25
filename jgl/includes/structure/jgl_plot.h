#include "jgl_includes.h"

struct Plot_data
{
	string name;
	float min;
	float max;
	size_t precision;

	Plot_data(string p_name = "Value", float p_min = 0.0f, float p_max = 100.0f)
	{
		name = p_name;
		min = p_min;
		max = p_max;
		precision = 0;
	}
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
	void draw_absciss();
	void draw_absciss_point(float value);
	void draw_ordinate();
	void draw_ordinate_point(float value);
	void save(string path);

	void actualize_point();

	void set_size(Vector2 p_size){size = p_size;actualize_point();}
	void set_margin(Vector2 p_margin){margin = p_margin;actualize_point();}
	void set_color(Color p_color){color = p_color;}

	void set_absciss(Plot_data p_absciss){absciss = p_absciss;}
	void set_ordinate(Plot_data p_ordinate){ordinate = p_ordinate;}

	void set_absciss_name(string p_name){absciss.name = p_name;}
	void set_absciss_min(float p_min){absciss.min = p_min;}
	void set_absciss_max(float p_max){absciss.max = p_max;}
	void set_absciss_precision(int p_precision){absciss.precision = p_precision;}

	void set_ordinate_name(string p_name){ordinate.name = p_name;}
	void set_ordinate_min(float p_min){ordinate.min = p_min;}
	void set_ordinate_max(float p_max){ordinate.max = p_max;}
	void set_ordinate_precision(int p_precision){ordinate.precision = p_precision;}

};
