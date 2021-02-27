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

using namespace std;

class Point
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

	friend double dist(const Point& a, const Point& b)
	{
		return sqrt((a.get_x() - b.get_x()) * (a.get_x() - b.get_x()) +
			(a.get_y() - b.get_y()) * (a.get_y() - b.get_y()));
	}
};

class Vector : public Point 
{
public:
	Vector() {};
	Vector(double, double);
	Vector(const Vector&);
	Vector(const Point&);

	friend double operator*(const Vector&, const Vector&);
	friend double vector_product(const Vector&, const Vector&);
};

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

	Polygon(vector<Point>);
	friend istream& operator>>(istream&, Polygon&);
	friend ostream& operator<<(ostream&, const Polygon&);

	friend Polygon operator+(const Polygon&, const Vector&);
	friend Polygon operator-(const Polygon&, const Vector&);

	void rotate_polygon(double,const Point&);
};