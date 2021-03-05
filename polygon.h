#pragma once
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include "Point.h"

using namespace std;

class Polygon
{
protected:
	vector <Point> points;
	Point center = Point(0, 0);
	double area = 0;
	double perimeter = 0;
	bool is_convex = false;
public:
	void set_center();
	void set_area();
	void set_perimeter();
	void set_convex();

	Point get_center() const;
	double get_area() const;
	double get_perimeter() const;
	bool get_convex() const;

	Polygon() {}
	Polygon(vector<Point>);
	friend istream& operator>>(istream&, Polygon&);
	friend ostream& operator<<(ostream&, const Polygon&);

	friend Polygon operator+(const Polygon&, const Vector&);
	friend Polygon operator-(const Polygon&, const Vector&);

	void rotate_polygon(double,const Point&);
};