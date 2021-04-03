#pragma once

#include "Point.h"
#include "Line.h"

class Triangle : public Object
{
private:
	Point A, B, C;

	// Length of sides opposite to points; area and perimeter
	double a, b, c, S, P; 
	// Length of altitudes
	double hA, hB, hC; 
	// Length of medians
	double mA, mB, mC; 
	// Length of bisectors
	double bA, bB, bC; 
	// Angles degrees in A, B, C
	double alpha, beta, gamma; 
	// Radiuses of inscribed and circumscribed circles
	double r, R;
	string type = "";

	// Init use all setters for triangle
	void init();
	// All of them calculated by formulas
	void set_area();
	void set_perimeter();
	void set_sides();
	void set_angles();
	void set_heights();
	void set_R();
	void set_r();
	void set_bisectors();
	void set_medians();
	void set_type();

	// Create triangle with given 1 or 2 points for calculating equations
	Triangle triangle_point_shift1(Point& n, Point& k, Point& m);
	Triangle triangle_point_shift2(Point& n, Point& k, Point& m);
public:
	Triangle(double, double, double, double, double, double);
	Triangle(const Point &, const Point &, const Point &);
	Triangle(vector<Point>);

	string get_type() const;
	double get_area() const;
	double get_perimeter() const;
	double get_R() const;
	double get_r() const;
	// Return array with the length of ...
	vector<double> get_medians() const;
	vector<double> get_sides() const;
	vector<double> get_altitudes() const;
	vector<double> get_bisectors() const;
	// Return array with the angles in degrees (sum of all ~ 180)
	vector<double> get_angles() const;

	// Check if 1 - inside 0 - on or -1 - outside
	int point_is_inside(const Point&);
	// For output
	friend ostream& operator<<(ostream&, Triangle&);
	// Check for rectangular triangle
	friend bool rectangular_check(double, double, double);
	// Check for points not on the same line
	friend bool points_check(const Point&, const Point&, const Point&);
	
	// Funcs for creating equations of bisector, altitude(height), midline
	Ray create_bisector(const Point&);
	Segment create_altitude(const Point&);
	Segment create_midline(const Point&, const Point&);

	// Function for drawing triangle
	void draw() const override;
};

bool points_check(const Point&, const Point&, const Point&);
