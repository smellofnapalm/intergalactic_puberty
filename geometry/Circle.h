#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Object.h"
#include "Point.h"
#include "Line.h"

using namespace std;

#define PI 3.14159265358979

class Circle : public Object
{
private:
	double _r = 0;
	Point _center = { 0, 0 };
public:
	Circle() {}
	Circle(Point, double);

	Point get_center() const;
	double get_r() const;
	void set_center(Point);
	void set_r(double);

	// Length of the circumfirence
	double get_length() const;
	double get_area() const;
	// Returns -1 if the point is out of the circle
	// Returns 0 if the point is on the circle
	// Returns 1 if the point is inside the circle
	int point_occurrence(const Point&, const Circle&);

	friend istream& operator>> (istream&, Circle&);
	friend ostream& operator<< (ostream&, const Circle&);
	friend bool operator==(const Circle&, const Circle&);

	// Return common points and if circles are equal return two random points
	friend vector<Point> circles_intersection(const Circle&, const Circle&);

	// Make a tangent line to a circle in a certain point
	static Line make_tangent_line(const Circle&, const Point&);

	// Calculate the distance from given point to circle
	double distance_to_point(const Point&);

	void draw() const override;
};


