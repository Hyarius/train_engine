#include "jgl.h"

c_plot::c_plot(Vector2 p_size, Plot_data p_absciss, Plot_data p_ordinate)
{
	color = Color(220, 220, 220);
	margin = Vector2(30, 30);
	text_size = 16;
	set_size(p_size);
	absciss = p_absciss;
	ordinate = p_ordinate;
	point_size = 5;
	line_size = 1;
	plot = new c_image(size.x, size.y, color);
}

c_plot::~c_plot()
{

}

void c_plot::clear()
{
	lines.clear();
}

void c_plot::actualize_point()
{
	origin = Vector2(margin.x, size.y - margin.y);
	pos_up = margin;
	pos_right = origin + Vector2(size.x - margin.x * 2, 0.0f);
	calc_axis_unit();
}

void c_plot::add_line(Color p_color)
{
	lines.push_back(Line(p_color));
}

void c_plot::add_point(Vector2 p_point, size_t line)
{
	if (lines.size() <= line)
		lines.resize(line + 1);

	lines[line].add_point(p_point);
}

void c_plot::set_line_color(size_t index, Color p_color)
{
	lines[index] = Line(p_color);
}

void c_plot::calc_axis_unit()
{
	ordinate_unit = (pos_up - origin) / (ordinate.max - ordinate.min);
	absciss_unit = (pos_right - origin) / (absciss.max - absciss.min);
}

void c_plot::initialize()
{
	plot = new c_image(size.x, size.y, color);
}

void c_plot::draw()
{
	draw_line(Color(0, 0, 0), origin, pos_right, 2);
	draw_line(Color(0, 0, 0), origin, pos_up, 2);
	draw_absciss();
	draw_ordinate();

	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].points.size(); j++)
		{
			draw_plot_point(lines[i].points[j], lines[i].color);
			if (j != 0)
				draw_plot_line(lines[i].points[j - 1], lines[i].points[j], lines[i].color);
		}
	}
}

void c_plot::draw_absciss()
{
	draw_text(absciss.name, pos_right - Vector2(calc_text_len(absciss.name, text_size), 20), text_size);
	for (float i = absciss.min; i <= absciss.max; i += absciss.delta)
		draw_absciss_point(i);
}

void c_plot::draw_plot_point(Vector2 point, Color color)
{
	float delta_x = point.x - absciss.min;
	float delta_y = point.y - ordinate.min;

	draw_point(color, origin + absciss_unit * delta_x + ordinate_unit * delta_y, point_size);
}

void c_plot::draw_plot_line(Vector2 point_a, Vector2 point_b, Color color)
{
	Vector2 tmp_a = origin + absciss_unit * (point_a.x - absciss.min) + ordinate_unit * (point_a.y - ordinate.min);
	Vector2 tmp_b = origin + absciss_unit * (point_b.x - absciss.min) + ordinate_unit * (point_b.y - ordinate.min);

	draw_line(color, tmp_a, tmp_b, line_size);
}

void c_plot::draw_absciss_point(float value)
{
	string text = ftoa(value, absciss.precision);
	float delta = value - absciss.min;
	draw_point(Color(0, 0, 0), origin + absciss_unit * delta, 5);
	draw_centred_text(text, origin + absciss_unit * delta + Vector2(0.0f, margin.y / 2));
}

void c_plot::draw_ordinate()
{
	draw_text(ordinate.name, Vector2(10, 10), text_size);
	for (float i = ordinate.min; i <= ordinate.max; i += ordinate.delta)
		draw_ordinate_point(i);
}

void c_plot::draw_ordinate_point(float value)
{
	string text = ftoa(value, ordinate.precision);
	float delta = value - ordinate.min;
	draw_point(Color(0, 0, 0), origin + ordinate_unit * delta, 5);
	draw_centred_text(text, origin + ordinate_unit * delta - Vector2(margin.x / 2, 0.0f));
}

void c_plot::save(string path)
{
	plot->active();
	draw();
	plot->save(path);
	plot->unactive();
}
