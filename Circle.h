#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Point.h"

using namespace std;

class Circle
{
private:
	double _r = 0;
	Point _a = {0, 0};
public:
	Circle() {}
	Circle(Point, double);

	Point get_a() const;
	double get_r() const;

	void set_a(Point);
	void set_r(double);

	friend istream& operator>> (istream&, Point&);
	friend ostream& operator<< (ostream&, const Point&);
};

