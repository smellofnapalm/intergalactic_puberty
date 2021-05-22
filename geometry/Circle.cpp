#include "Circle.h"

double sqr(double a) { return a * a; }

Circle::Circle(const Point& center, double r)
{
	if (r <= 0)
		throw exception("Radius of the circle should be > 0!");

	set_center(center);
	set_r(r);
}

double Circle::get_length() const
{
	return (2 * PI * _r);
}

double Circle::get_area() const
{
	return (PI * _r * _r);
}

int Circle::point_occurrence(const Point& p, const Circle& circle) const
{
	double temp = 0;
	temp = sqr((p.get_x() - circle._center.get_x())) 
		+ sqr((p.get_y() - circle._center.get_y())) 
		- sqr(circle.get_r());

	if (temp > 0) return -1;
	if (temp < 0) return 1;
	return 0;
}

Line Circle::make_tangent_line(const Circle& circle, const Point& p)
{
	double x0 = circle.get_center().get_x();
	double y0 = circle.get_center().get_y();
	double x1 = p.get_x();
	double y1 = p.get_y();
	double r = circle.get_r();
	return Line(x1 - x0, y1 - y0, -x1 * x0 - y1 * y0 + x0 * x0 + y0 * y0 - r * r);
}

void Circle::draw() const
{
	if (is_filled)
	{
		glBegin(GL_POLYGON);

		glColor3ub(get_color().R, get_color().G, get_color().B);
		int N = 500;
		glVertex2f(_center.get_x(), _center.get_y());
		for (int i = 0; i <= N; i++)
		{
			double angle = 2 * PI * i / N;
			glVertex2f(_r * cos(angle) + _center.get_x(), _r * sin(angle) + _center.get_y());
		}

		glEnd();
	}
	
	glBegin(GL_LINE_LOOP);

	glColor3ub(line_loop_color.R, line_loop_color.G, line_loop_color.B);
	int N = 500;
	glVertex2f(_center.get_x(), _center.get_y());
	for (int i = 0; i <= N; i++)
	{
		double angle = 2 * PI * i / N;
		glVertex2f(_r * cos(angle) + _center.get_x(), _r * sin(angle) + _center.get_y());
	}

	glEnd();
}

istream& operator>> (istream& in, Circle& circle)
{
	Point center;
	double r;
	in >> center >> r;
	circle = Circle(center, r);
	return in;
}

ostream& operator<< (ostream& out, const Circle& circle)
{
	out << "Circle equation:" << endl;

	if (circle.get_center() == Point(0, 0))
		out << "x^2 + y^2 = " << sqr(circle.get_r()) << endl;
	else
		out << "(x - (" << circle._center.get_x() 
			<< "))^2 + (y - (" << circle._center.get_y() 
			<< "))^2 = " << sqr(circle.get_r()) << endl;

	out << "The center of the circle is:\n";
	out << circle.get_center() << endl;
	out << "The radius of the circle is:\n";
	out << circle.get_r() << endl;

	return out;
}

bool operator==(const Circle& circle1, const Circle& circle2)
{
	return circle1._center == circle2._center && circle1._r == circle2._r;
}

double Circle::distance_to_point(const Point& p) const
{
	/*
	If point is inside - radius minus distance from point to the center
	If point is outside - distance from point to the center minus radius
	*/
	Point c = get_center();
	double r = get_r();
	double t = sqr((p.get_x() - c.get_x())) + sqr((p.get_y() - c.get_y())) - sqr(r);

	if (t == 0) 
		return 0;
	else if (t > 0)  
		return (dist(p, c) - r);
	return (r - dist(p, c));
}

vector<Point> circles_intersection(const Circle& o1, const Circle& o2)
{
	/*
	We solve the system of equations of a straight line and a circle, 
	obtained by subtracting the second circle from the first.
	A,B,C - Line ñoefficients
	xi, yi - coordinates of centre of i circle (i = 1,2)
	There are 3 cases: if A = B = 0, then we check the radiuses, because (x1,y1) == (x2,y2)
	if A != 0 we can divide on it and put in the system. Then we solve the quadratic equation where can be 0-2 roots.
	So then there are 0-2 points of intersection.
	the same way if B != 0
	You can solve the system on your way by creating substitutions and then have big formulas for a,b,c as example.
	*/

	Point  c1 = o1.get_center();
	Point  c2 = o2.get_center();
	double x1 = c1.get_x(),
		   x2 = c2.get_x(),
		   y1 = c1.get_y(),
		   y2 = c2.get_y(),
		   r1 = o1.get_r(),
		   r2 = o2.get_r(),
		   A = 2 * (x1 - x2),
		   B = 2 * (y1 - y2),
		   C = x2 * x2 + y2 * y2 - x1 * x1 - y1 * y1 + r1 * r1 - r2 * r2;

	if (A == 0 && B == 0)
	{
		// If no intersecton
		if (r1 != r2) return {};

		// If they are equal then return two points on a diameter
		return { o1.get_center() + Point(r1, 0), o1.get_center() - Point(r1, 0) };
	}

	if (A != 0)
	{
		double a = (B * B) / (A * A) + 1;
		double b = 2 * (B * C / (A * A) + (B * x1 / A) - y1);
		double c = y1 * y1 - r1 * r1 + sqr(-(C / A) - x1);

		double D = b * b - 4 * a * c;
		// No roots
		if (D < 0) return {};
		// One root
		else if (D == 0)
		{
			double y = -b / (2 * a);
			double x = -1 / A * (B * y + C);
			return { Point(x,y) };
		}
		// Two roots
		else
		{
			double x01, y01, x02, y02;
			y01 = ((-b + sqrt(D)) / (2 * a));
			y02 = ((-b - sqrt(D)) / (2 * a));
			x01 = -1 / A * (B * y01 + C);
			x02 = -1 / A * (B * y02 + C);
			return { Point(x01, y01), Point(x02, y02) };
		}
	}

	else if (B != 0)
	{

		double a = (A * A) / (B * B) + 1;
		double b = 2 * ((A * C) / (B * B) + (A * y1) / B - x1);
		double c = x1 * x1 - r1 * r1 + sqr(-(C / B) - y1);

		double D = b * b - 4 * a * c;
		// No roots
		if (D < 0) return {};
		// One root
		else if (D == 0)
		{
			double y = -b / (2 * a);
			double x = -1 / B * (A * y + C);
			return { Point(x,y) };
		}
		// Two roots
		else
		{
			double x01, y01, x02, y02;
			x01 = ((-b + sqrt(D)) / (2 * a));
			x02 = ((-b - sqrt(D)) / (2 * a));
			y01 = -1 / B * (A * x01 + C);
			y02 = -1 / B * (A * x02 + C);
			return { Point(x01, y01), Point(x02, y02) };
		}
	}

	return {};
}
