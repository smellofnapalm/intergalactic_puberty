#pragma once

#include "Line.h"
#include "Triangle.h"

using namespace std;

class Polygon : public Object
{
protected:
	vector <Point> points;
	Point center = Point(0, 0);
	double area = 0;
	double perimeter = 0;
	bool is_convex = false;

	// These formulas are taken from Wikipedia
	void set_center();
	void set_area();

	void set_perimeter();

	// Check sign of vector products
	void set_convex();
public:
	Point get_center() const { return center; }
	double get_area() const { return area; }
	double get_perimeter() const { return perimeter; }
	bool get_convex() const { return is_convex; };
	vector <Point> get_points() const { return points; };

	Polygon() {}
	Polygon(vector<Point>);
	friend istream& operator>>(istream&, Polygon&);
	friend ostream& operator<<(ostream&, const Polygon&);

	// Shift polygon on some vector
	friend Polygon operator+(const Polygon&, const Vector&);
	friend Polygon operator-(const Polygon&, const Vector&);

	const Point operator[](size_t index) const { return points[index]; }

	// Rotate polygon on some angle (counter-clockwise of course) with respect to certain point
	void rotate_polygon(double, const Point&);

	// Check if 1 - inside 0 - on or -1 - outside
	int point_is_inside(const Point&);
	// Return bisector from given point
	Ray create_bisector(const Point&);

	void draw() const override;
	void shift_by_vector(const pair<double, double>& p) override { for (size_t i = 0; i < points.size(); i++) points[i].shift_by_vector(p); *this = Polygon(points); }

	friend Polygon convex_hull(const vector<Point>&);
	friend Polygon convex_hull(const Polygon&);
};