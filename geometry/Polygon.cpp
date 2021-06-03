#include "Polygon.h"
#include <iostream>

// POLYGON FUNCTIONS

Polygon convex_hull(const vector<Point>& given);

Polygon::Polygon(vector <Point> v)
{
	if (v.size() <= 2) 
		throw exception("Polygon must contain > 2 points!");

	this->points = v;
	set_convex();

	// We use only convex polygons!
	if (!is_convex) *this = convex_hull(*this);
	is_convex = true;

	set_area();
	set_perimeter();
	set_center();
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

void Polygon::rotate_polygon(double angle, const Point& p)
{
	int n = points.size();
	for (int i = 0; i < n; i++)
		points[i] = Vector::rotate(points[i], angle, p);
}

void Polygon::draw() const
{
	if (is_filled)
	{
		glBegin(GL_POLYGON);

		glColor3ub(get_color().R, get_color().G, get_color().B);
		for (size_t i = 0; i < points.size(); i++) glVertex2d(points[i].get_x(), points[i].get_y());
		glVertex2d(points[0].get_x(), points[0].get_y());

		glEnd();
	}

	glBegin(GL_LINE_LOOP);

	glColor3ub(line_loop_color.R, line_loop_color.G, line_loop_color.B);
	for (size_t i = 0; i < points.size(); i++) glVertex2d(points[i].get_x(), points[i].get_y());
	//glVertex2d(points[0].get_x(), points[0].get_y());

	glEnd();
}

istream& operator>>(istream& in, Polygon& polygon)
{
	int n;
	in >> n;
	vector<Point> points;
	points.resize(n);
	for (int i = 0; i < n; i++) 
		in >> points[i];
	try
	{
		polygon = Polygon(points);
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
	}
	return in;
}

ostream& operator<<(ostream& out, const Polygon& polygon)
{
	// If it is empty
	if (polygon.points.size() == 0) 
		return out;

	out << "The size of polygon is " << polygon.points.size() << endl;
	out << "The points of the polygon:\n";
	for (size_t i = 0; i < polygon.points.size(); i++) 
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

int Polygon::point_is_inside(const Point& p)
{
	/*
	Every f > 0 or f < 0 => inside
	If exist !f => outside
	If f == 0 && on side => on side
	*/

	bool poz = false, neg = false;
	double f;

	for (size_t i = 0; i <= points.size(); ++i)
	{
		if (i == points.size())
			f = (points[i].get_x() - p.get_x() * (points[0].get_y() - points[i].get_y())) - ((points[0].get_x() - points[i].get_x()) * (points[i].get_y() - p.get_y()));
		else
			f = (points[i].get_x() - p.get_x() * (points[i + 1].get_y() - points[i].get_y())) - ((points[i + 1].get_x() - points[i].get_x()) * (points[i].get_y() - p.get_y()));

		if ((f > 0 && neg) || (f < 0 && poz)) return -1;
		if (f == 0) {
			int j = 0;
			if (i != points.size()) {
				j = i + 1;
			}
			Segment s(points[i], points[j]);
			if (s.is_on(p) == 1) {
				return 0;
			}
		}
		if (f > 0 && !poz) poz = true;
		if (f < 0 && !neg) neg = true;
	}
	return 1;
}

Ray Polygon::create_bisector(const Point& p) 
{
	// Check for point p in polygon
	int k = -1, n = points.size();
	for (size_t i = 0; i < n; i++)
	{
		if (p == points[i])
		{
			k = i;
			break;
		}
	}
	if (k == -1) 
		throw "Point is not in polygon!";
	Triangle t = Triangle(points[(k - 1 + n) % n], points[k], points[(k + 1) % n]);
	return t.create_bisector(p);
}

// Realization is taken from
// https://habr.com/ru/post/144921/
Polygon convex_hull(const vector<Point>& given)
{
	int n = given.size();
	Point* a = new Point[n];
	{
		int minx = 0;
		for (int i = 0; i < n; i++)
		{
			a[i] = given[i];
			if (a[i].get_x() < a[minx].get_x())
				minx = i;
		}
		Point temp = a[minx];
		a[minx] = a[0];
		a[0] = temp;
	}
	for (int i = 2; i < n; i++)
	{
		int j = i;
		while (j > 1 && rotate(a[0], a[j - 1], a[j]) < 0)
		{
			Point temp = a[j];
			a[j] = a[j-1];
			a[j-1] = temp;
			j--;
		}
	}

	vector <Point> shell;
	shell.push_back(a[0]);
	shell.push_back(a[1]);
	for (int i = 2; i < n; i++)
	{
		shell.push_back(a[i]);
		int size = shell.size();
		while ((rotate(shell[size - 3], shell[size - 2], shell[size - 1])) < 0 && size != 2)
		{
			shell.erase(shell.begin() + (size - 2));
			size--;
		}
	}
	return Polygon(shell);
}

Polygon convex_hull(const Polygon& p)
{
	return convex_hull(p.get_points());
}
