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

double Circle::get_Lenght()
{
	return 2 * PI * _r;
}

double Circle::get_Square()
{
	return PI* _r* _r;
}

istream& operator>> (istream& in, Circle& o)
{
	Point center;
	double r;
	in >> center >> r;
	o(center, r);
	return in;
}

ostream& operator<< (ostream&, const Circle& o)
{
	cout << "Circle equation" << endl;
	cout << "(x-" << o._centre.get_x << ")^2 + (y-" << o._centre.get_y << ")^2 = " << o.get_r * o.get_r << "^2" << endl;
}

bool operator==(const Circle& o1, const Circle& o2)
{
	return(o1._centre == o2._centre && o1._r == o2._r)
}
