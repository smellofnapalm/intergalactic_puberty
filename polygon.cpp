#include "polygon.h"

// POLYGON FUNCTIONS

Polygon::Polygon(vector <Point> v)
{
	if (v.size() <= 2) 
		throw "Polygon must contain > 2 points!";
	this->points = v;
	set_area();
	set_perimeter();
	set_center();
	set_convex();
}

void Polygon::set_center()
{
	double avr_x = 0, avr_y = 0;
	int n = points.size();
	for (int i = 0; i < n; i++)
	{
		avr_x += (points[i].get_x() + points[(i + 1) % n].get_x()) 
			* (points[i].get_x() * points[(i + 1) % n].get_y()
			- points[i].get_y() * points[(i + 1) % n].get_x());
		avr_y += (points[i].get_y() + points[(i + 1) % n].get_y()) 
			* (points[i].get_x() * points[(i + 1) % n].get_y()
			- points[i].get_y() * points[(i + 1) % n].get_x());
	}
	avr_x /= 6 * area;
	avr_y /= 6 * area;
	center = { avr_x, avr_y };
}

void Polygon::set_area()
{
	int n = points.size();
	area = 0;
	for (int i = 0; i < n; i++)
		area += 0.5 * (points[i].get_x() * points[(i + 1) % n].get_y()
			- points[i].get_y() * points[(i + 1) % n].get_x());
}

void Polygon::set_perimeter()
{
	int n = points.size();
	perimeter = 0;
	for (int i = 0; i < n; i++)
		perimeter += dist(points[i], points[(i + 1) % n]);
}

void Polygon::set_convex()
{
	int n = points.size();
	double last = 0;
	for (int i = 0; i < n; i++)
	{
		Vector a, b;
		a = Vector(points[(i + 1) % n].get_x() - points[i].get_x(), points[(i + 1) % n].get_y() - points[i].get_y());
		b = Vector(points[(i - 1 + n) % n].get_x() - points[i].get_x(), points[(i - 1 + n) % n].get_y() - points[i].get_y());
		if (vector_product(a, b) * last < 0 && i > 0)
		{
			is_convex = false;
			return;
		}
		last = vector_product(a, b);
	}
	is_convex = true;
}

Point Polygon::get_center() const
{
	return center;
}

double Polygon::get_area() const
{
	return area;
}

double Polygon::get_perimeter() const
{
	return perimeter;
}

bool Polygon::get_convex() const
{
	return is_convex;
}
Polygon operator+(const Polygon& polygon, const Vector& shift)
{
	vector <Point> new_points;
	for (const Point& point : polygon.points)
		new_points.push_back(point + shift);
	return Polygon(new_points);
}

Polygon operator-(const Polygon& polygon, const Vector& shift)
{
	vector <Point> new_points;
	for (const Point& point : polygon.points)
		new_points.push_back(point - shift);
	return Polygon(new_points);
}

void Polygon::rotate_polygon(double angle,const Point& p)
{
	int n = points.size();
	for (int i = 0; i < n; i++)
	{
		points[i] = points[i] - p;
		points[i].set_x(cos(angle) * points[i].get_x() - sin(angle) * points[i].get_y());
		points[i].set_y(sin(angle) * points[i].get_x() + cos(angle) * points[i].get_y());
		points[i] = points[i] + p;
	}
}

istream& operator>>(istream& in, Polygon& polygon)
{
	int n;
	in >> n;
	vector<Point> points;
	points.resize(n);
	for (int i = 0; i < n; i++) cin >> points[i];
	polygon = Polygon(points);
	return in;
}

ostream& operator<<(ostream& out, const Polygon& polygon)
{
	out << "The size of polygon is " << polygon.points.size() << endl;
	out << "The points of the polygon:\n";
	for (int i = 0; i < polygon.points.size(); i++) 
		out << polygon.points[i] << endl;
	out << "The center of the polygon is " << polygon.get_center() << endl;
	out << "The area of the polygon is " << polygon.get_area() << endl;
	out << "The perimeter of the polygon is " << polygon.get_perimeter() << endl;
	if (polygon.get_convex())
		out << "The polygon is convex!\n";
	else
		out << "The polygon isn't convex!\n";
	return out;
}

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
