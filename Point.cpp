#include "Point.h"
// POINT FUNCTIONS

// Setters and getters for coordinates

double Point::get_x() const { return x; }
double Point::get_y() const { return y; }

void Point::set_x(double x) { this->x = x; }
void Point::set_y(double y) { this->y = y; }


Point::Point()
{
	x = 0;
	y = 0;
}

Point::Point(double a, double b)
{
	this->x = a;
	this->y = b;
}

Point::Point(const Point& p)
{
	this->x = p.x;
	this->y = p.y;
}

bool operator==(const Point& a, const Point& b)
{
	return (a.x == b.x && a.y == b.y);
}

bool operator!=(const Point& a, const Point& b)
{
	return !(a == b);
}

istream& operator>>(istream& in, Point& p)
{
	double a, b;
	in >> a >> b;
	p = { a, b };
	return in;
}

ostream& operator<<(ostream& out, const Point& p)
{
	out << p.x << " " << p.y;
	return out;
}

Point operator+(const Point& a, const Point& b)
{
	return Point(a.x + b.x, a.y + b.y);
}

Point operator*(double lambda, const Point& p)
{
	return Point(lambda * p.x, lambda * p.y);
}

Point operator-(const Point& a, const Point& b)
{
	return Point(a + (-b));
}

Point operator-(const Point& a)
{
	return Point(-a.x, -a.y);
}

Point& Point::operator=(const Point& p)
{
	this->x = p.x;
	this->y = p.y;
	return *this;
}

// VECTOR FUNCTIONS

double operator*(const Vector& a, const Vector& b)
{
	return a.x * b.x + a.y * b.y;
}

double vector_product(const Vector& a, const Vector& b)
{
	return a.get_x() * b.get_y() - a.get_y() * b.get_x();
}

Vector::Vector(double x, double y)
{
	this->set_x(x);
	this->set_y(y);
}

Vector::Vector(const Vector& v)
{
	this->set_x(v.get_x());
	this->set_y(v.get_y());
}

Vector::Vector(const Point& p)
{
	this->set_x(p.get_x());
	this->set_y(p.get_y());
}
