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
	out << "(" << p.x << ", " << p.y << ")";
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

bool operator<(const Point& a, const Point& b)
{
	return a.x + a.y < b.x + b.y;
}

double dist(const Point& a, const Point& b)
{
	return sqrt((a.get_x() - b.get_x()) * (a.get_x() - b.get_x()) +
		(a.get_y() - b.get_y()) * (a.get_y() - b.get_y()));
}

Point& Point::operator=(const Point& p)
{
	this->x = p.x;
	this->y = p.y;
	return *this;
}

void Point::draw() const
{
	glEnable(GL_POINT_SMOOTH);
	glPointSize(15);
	glBegin(GL_POINTS);

	glColor3ub(get_color().R, get_color().G, get_color().B);

	glVertex2d(x, y);
	glDisable(GL_POINT_SMOOTH);
	glEnd();
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

Vector Vector::rotate(const Vector& v, double angle, const Point& center)
{
	Vector new_v = v, temp;
	new_v = new_v - center;
	temp = new_v;
	new_v.set_x(cos(angle) * temp.get_x() - sin(angle) * temp.get_y());
	new_v.set_y(sin(angle) * temp.get_x() + cos(angle) * temp.get_y());
	new_v = new_v + center;
	return new_v;
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

double Vector::length() const
{
	return sqrt(x*x + y*y);
}

int rotate(const Point& A, const Point B, const Point C)
{
	return ((B.get_x() - A.get_x()) * (C.get_y() - B.get_y()) - (B.get_y() - A.get_y()) * (C.get_x() - B.get_x()));
}
