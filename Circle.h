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

	double get_Lenght();
	double get_Square();

	friend istream& operator>> (istream&, Circle&);
	friend ostream& operator<< (ostream&, const Circle&);
	friend bool operator==(const Circle&, const Circle&);
};

