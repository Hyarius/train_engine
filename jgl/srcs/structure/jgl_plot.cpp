#include "jgl.h"

c_plot::c_plot(Vector2 p_size, Plot_data p_absciss, Plot_data p_ordinate)
{
	color = Color(220, 220, 220);
	margin = Vector2(30, 30);
	text_size = 16;
	set_size(p_size);
	absciss = p_absciss;
	ordinate = p_ordinate;
}

c_plot::~c_plot()
{

}

void c_plot::actualize_point()
{
	origin = Vector2(margin.x, size.y - margin.y);
	pos_up = margin;
	pos_right = origin + Vector2(size.x - margin.x * 2, 0.0f);
	ordinate_unit = (pos_up - origin) / (ordinate.max - ordinate.min);
	absciss_unit = (pos_right - origin) / (absciss.max - absciss.min);
}

void c_plot::initialize()
{
	plot = new c_image(size.x, size.y, color);
}

void c_plot::draw()
{

	plot->active();

	draw_line(Color(0, 0, 0), origin, pos_right, 2);
	draw_line(Color(0, 0, 0), origin, pos_up, 2);
	draw_absciss();
	draw_ordinate();
	plot->unactive();
}

void c_plot::draw_absciss()
{
	draw_text(absciss.name, pos_right - Vector2(calc_text_len(absciss.name, text_size), 20), text_size);
	draw_absciss_point(absciss.min);
	draw_absciss_point(absciss.max);
}

void c_plot::draw_absciss_point(float value)
{
	string text = ftoa(value, absciss.precision);
	float delta = value - absciss.min;
	draw_point(Color p_color, Vector2 center, int width, c_viewport *viewport);
	draw_centred_text(text, origin + absciss_unit * delta + Vector2(0.0f, margin.y / 2));
}

void c_plot::draw_ordinate()
{
	draw_text(ordinate.name, Vector2(10, 10), text_size);
	draw_ordinate_point(ordinate.min);
	draw_ordinate_point(ordinate.max);
}

void c_plot::draw_ordinate_point(float value)
{
	string text = ftoa(value, ordinate.precision);
	float delta = value - ordinate.min;
	draw_centred_text(text, origin + ordinate_unit * delta - Vector2(margin.x / 2, 0.0f));
}

void c_plot::save(string path)
{
	plot->save(path);
}
