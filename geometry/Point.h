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

#include "Object.h"
#include "glut/glut.h"

using namespace std;

class Point : public Object
{
protected:
	double x, y;
public:
	double get_x() const;
	double get_y() const;

	void set_x(double);
	void set_y(double);

	Point();
	Point(double, double);
	Point(const Point&);
	Point& operator=(const Point& p);

	friend bool operator==(const Point&, const Point&);
	friend bool operator!=(const Point&, const Point&);

	friend istream& operator>>(istream&, Point&);
	friend ostream& operator<<(ostream&, const Point&);

	friend Point operator+(const Point&, const Point&);
	friend Point operator*(double, const Point&);
	friend Point operator-(const Point&, const Point&);
	friend Point operator-(const Point&);
	friend bool operator<(const Point&, const Point&);

	friend double dist(const Point&, const Point&);

	void draw() const override;
	void shift_by_vector(const pair<double, double>& p) override { x += p.first; y += p.second; }

	//Three points are given A,B,C. The function determines which side of the AB vector is the point C (left or right)
	friend int rotate(const Point&, const Point, const Point);
};

// Some special point we return if there is no such point
const Point UNDEF = { 1e9, 1e9 };

class Vector : public Point
{
public:
	Vector() {};
	Vector(double, double);
	Vector(const Vector&);
	Vector(const Point&);

	// Scalar product of vectors
	friend double operator*(const Vector&, const Vector&);

	friend double vector_product(const Vector&, const Vector&);
	static Vector rotate(const Vector&, double, const Point&);
	double length() const;
};