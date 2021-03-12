#include "Circle.h"

Circle::Circle(Point center, double r)
{
	set_center(center);
	set_r(r);
}

Point Circle::get_center() const { return _center; }
double Circle::get_r() const { return _r; }

void Circle::set_center(Point center) { _center = center; }
void Circle::set_r(double r) { _r = r; }

double Circle::get_length()
{
	return (2 * PI * _r);
}

double Circle::get_area()
{
	return (PI * _r * _r);
}

Line Circle::make_tangent_line(const Circle& o, const Point& p)
{
	double x0 = o.get_center().get_x();
	double y0 = o.get_center().get_y();
	double x1 = p.get_x();
	double y1 = p.get_y();
	double r = o.get_r();
	return Line(x1 - x0, y1 - y0, -x1*x0 - y1*y0 + x0*x0 + y0*y0 - r*r);
}

istream& operator>> (istream& in, Circle& o)
{
	Point center;
	double r;
	in >> center >> r;
	o = Circle(center, r);
	return in;
}

ostream& operator<< (ostream& out, const Circle& o)
{
	out << "Circle equation" << endl;
	out << "(x-" << o._center.get_x() << ")^2 + (y-" << o._center.get_y() << ")^2 = " << o.get_r() * o.get_r() << endl;
	return out;
}

bool operator==(const Circle& o1, const Circle& o2)
{
	return(o1._center == o2._center && o1._r == o2._r);
}
