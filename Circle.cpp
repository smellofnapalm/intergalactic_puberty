#include "Circle.h"

Circle::Circle(Point a, double r)
{
	set_a(a);
	set_r(r);
}

Point Circle::get_a() const { return _a; }
double Circle::get_r() const { return _r; }

void Circle::set_a(Point a) { _a = a; }
void Circle::set_r(double r) { _r = r; }
