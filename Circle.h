#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Point.h"
#include "Line.h"

using namespace std;

#define PI 3.14159265358979

class Circle
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

	double get_length();
	double get_area();

	friend istream& operator>> (istream&, Circle&);
	friend ostream& operator<< (ostream&, const Circle&);
	friend bool operator==(const Circle&, const Circle&);

	// Make a tangent line to a circle in a certain point
	static Line make_tangent_line(const Circle&, const Point&);
};

