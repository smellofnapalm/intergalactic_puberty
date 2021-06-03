#pragma once

#include "Line.h"
#include <vector>

using namespace std;

const double PI = 3.141592653589;

class Circle : public Object
{
private:
	double _r = 0;
	Point _center = { 0, 0 };
public:
	Circle() {}
	Circle(const Point&, double);

	Point get_center() const { return _center; };
	double get_r() const { return _r; };
	void set_center(const Point& center) { _center = center; };
	void set_r(double r) { _r = r; };

	// Length of the circumfirence
	double get_length() const;
	double get_area() const;

	// Returns -1 if the point is out of the circle
	// Returns 0 if the point is on the circle
	// Returns 1 if the point is inside the circle
	int point_occurrence(const Point&, const Circle&) const;

	friend istream& operator>> (istream&, Circle&);
	friend ostream& operator<< (ostream&, const Circle&);
	friend bool operator==(const Circle&, const Circle&);

	// Return common points and if circles are equal return two random points
	friend vector<Point> circles_intersection(const Circle&, const Circle&);

	// Make a tangent line to a circle in a certain point
	static Line make_tangent_line(const Circle&, const Point&);

	// Calculate the distance from given point to circle
	double distance_to_point(const Point&) const;

	void draw() const override;
	void shift_by_vector(const pair<double, double>& p) override { Vector v = Vector(p.first, p.second); *this = Circle(_center + v, _r); }
};


