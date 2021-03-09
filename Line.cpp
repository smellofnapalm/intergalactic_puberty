#include "Line.h"

// SETTERS

void Line::set_p0(double x0)
{
	p0 = { x0, (*this)[x0] };
}

void Line::set_p0()
{
	p0 = { 0, (*this)[0] };
}

void Line::set_v()
{
	v = { -B, A };
	v = (1 / v.length()) * v;
}

void Line::set_n()
{
	n = { A, B };
	n = (1 / n.length()) * n;
}

void Line::set_coef()
{
	A = n.get_x();
	B = n.get_y();
	C = -(A * p0.get_x() + B * p0.get_y());
}

// CONSTUCTORS

Line::Line(double _A, double _B, double _C) : A(_A), B(_B), C(_C)
{
	set_p0();
	set_v();
	set_n();
}

Line::Line(const Point& _p0, const Point& _p1) : p0(_p0)
{
	v = _p1 - _p0;
	v = (1 / v.length()) * v;
	n = { -v.get_y(), v.get_x() };
	set_coef();
}

Line::Line(const Point& _p0, const Vector& _v) : p0(_p0), v(_v)
{
	v = (1 / v.length()) * v;
	n = { -v.get_y(), v.get_x() };
	set_coef();
}

// OPERATORS

double Line::operator[](double x0) const
{
	if (get_B() == 0) return 0;
	return -(get_A()*x0 + get_C())/get_B();
}

istream& operator>>(istream& in, Line& l)
{
	Point a, b;
	in >> a >> b;
	l = Line(a, b);
	return in;
}

ostream& operator<<(ostream& out, const Line& l)
{
	out << "The equation of the line is:\n";
	out << l.A << "*x + " << l.B << "*y + " << l.C << endl;
	out << "The initial point (p0) and directing vector (v) are:\n";
	out << "p0 = " << l.p0 << endl;
	out << "v = " << l.v << endl;
	out << "The normal vector (n) is:\n";
	out << "n = " << l.n << endl;
	return out;
}

istream& operator>>(istream& in, Ray& r)
{
	Point a, b;
	in >> a >> b;
	r = Ray(a, b);
	return in;
}

istream& operator>>(istream& in, Segment& s)
{
	Point a, b;
	in >> a >> b;
	s = Segment(a, b);
	return in;
}

Ray::Ray(const Line& l, double x0, double x1)
{
	A = l.get_A();
	B = l.get_B();
	C = l.get_C();

	p0 = { x0, l[x0] };
	p1 = { x1, l[x1] };
	v = 1 / ((Vector)(p1 - p0)).length() * (Vector)(p1 - p0);
	n = { -v.get_y(), v.get_x() };
}

Ray::Ray(const Point& p0, const Point& p1)
{
	Line l = Line(p0, p1);
	(*this) = Ray(l, p0.get_x(), p1.get_y());
}

Segment::Segment(const Line& l, double x0, double x1)
{
	A = l.get_A();
	B = l.get_B();
	C = l.get_C();

	p0 = { x0, l[x0] };
	p1 = { x1, l[x1] };
	v = 1 / ((Vector)(p1 - p0)).length() * (Vector)(p1 - p0);
	n = { -v.get_y(), v.get_x() };

	avr_point = 0.5 * (p0 + p1);
}

Segment::Segment(const Point& a, const Point& b)
{
	Line l = Line(a, b);
	(*this) = Segment(l, a.get_x(), b.get_x());
}
