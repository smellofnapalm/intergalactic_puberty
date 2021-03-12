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

bool Line::is_on(const Point& p)
{
	return A * p.get_x() + B * p.get_y() + C == 0.0;
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

bool operator==(const Line& l1, const Line& l2)
{
	return l1.A == l2.A && l1.B == l2.B && l1.C == l2.C;
}

bool are_parallel(const Line& l1, const Line& l2)
{
	return l1.A == l2.A && l1.B == l2.B;
}

Line make_parallel_line(const Line& l, const Point& p)
{
	return Line(p, l.v);
}

Point intersection(const Line& l1, const Line& l2)
{
	double x, y;
	if (l1 == l2 || are_parallel(l1, l2)) return { 1e9, 1e9 };
	x = -(l1.C * l2.B - l2.C * l1.B) / (l1.A * l2.B - l2.A * l1.B);
	y = -(l1.A * l2.C - l2.A * l1.C) / (l1.A * l2.B - l2.A * l1.B);
	return { x, y };
}

istream& operator>>(istream& in, Ray& r)
{
	Point a, b;
	in >> a >> b;
	r = Ray(a, b);
	return in;
}

Point ray_intersection(const Ray& r1, const Ray& r2)
{
	Point ans = intersection(r1, r2);
	if (r1.p1.get_x() > r1.p0.get_x() && r2.p1.get_x() > r2.p0.get_x())
	{
		if (ans.get_x() >= max(r1.p0.get_x(), r2.p0.get_x()))
			return ans;
	}
	else if (r1.p1.get_x() > r1.p0.get_x() && r2.p1.get_x() < r2.p0.get_x())
	{
		if (ans.get_x() >= r1.p0.get_x() && ans.get_y() <= r2.p0.get_x())
			return ans;
	}
	else if (r1.p1.get_x() < r1.p0.get_x() && r2.p1.get_x() > r2.p0.get_x())
	{
		if (ans.get_x() <= r1.p0.get_x() && ans.get_y() >= r2.p0.get_x())
			return ans;
	}
	else if (r1.p1.get_x() < r1.p0.get_x() && r2.p1.get_x() < r2.p0.get_x())
	{
		if (ans.get_x() <= min(r1.p0.get_x(), r2.p0.get_x()))
			return ans;
	}
	return INF;
}

istream& operator>>(istream& in, Segment& s)
{
	Point a, b;
	in >> a >> b;
	s = Segment(a, b);
	return in;
}

Point segment_intersection(const Segment& s1, const Segment& s2)
{
	Point ans = intersection(s1, s2);
	double x = ans.get_x(), y = ans.get_y();
	if (x >= min(s1.p0.get_x(), min(s1.p1.get_x(), min(s2.p0.get_x(), s2.p1.get_x()))) &&
		x <= max(s1.p0.get_x(), min(s1.p1.get_x(), min(s2.p0.get_x(), s2.p1.get_x()))) &&
		y >= min(s1.p0.get_y(), min(s1.p1.get_y(), min(s2.p0.get_y(), s2.p1.get_y()))) &&
		y <= max(s1.p0.get_y(), min(s1.p1.get_y(), min(s2.p0.get_y(), s2.p1.get_y())))) return ans;
	return INF;
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

bool Ray::is_on(const Point& p)
{
	return (A*p.get_x() + B*p.get_y() + C == 0)
	&& (p.get_x() - p0.get_x())*(p1.get_x() - p0.get_x()) >= 0;
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

bool Segment::is_on(const Point& p)
{
	return A*p.get_x() + B*p.get_y() + C == 0 &&
	(p.get_x() - p0.get_x())*(p.get_x() - p1.get_x()) <= 0;
}
