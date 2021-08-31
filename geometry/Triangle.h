#pragma once

#include "Point.h"
#include "Line.h"
#include "Circle.h"

// CHECK THIS FUNCTION RESULT BEFORE CREATING TRIANGLE!
// Check for points not on the same line
bool points_check(const Point&, const Point&, const Point&);

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
	Triangle triangle_point_shift1(const Point&);
	Triangle triangle_point_shift2(Point&, Point&);
public:
	Triangle(double, double, double, double, double, double);
	Triangle(const Point &, const Point &, const Point &);
	~Triangle() {}

	Point getA() const { return A; }
	Point getB() const { return B; }
	Point getC() const { return C; }
	string get_type() const { return type; };
	double get_area() const { return S; };
	double get_perimeter() const { return P; };
	double get_R() const { return R; };
	double get_r() const { return r; };
	// Return array with the length of ...
	vector<double> get_medians() const;
	vector<double> get_sides() const;
	vector<double> get_altitudes() const;
	vector<double> get_bisectors() const;
	// Return array with the angles in degrees (sum of all ~ 180)
	vector<double> get_angles() const;

	// Check if 1 - inside 0 - on or -1 - outside
	int point_is_inside(const Point&) const;
	// For output
	friend ostream& operator<<(ostream&, Triangle&);
	
	// Funcs for creating equations of bisector, altitude(height), midline, median
	// Given point - begin of bisector, altitude or median
	Ray create_bisector(const Point&);
	Segment create_altitude(const Point&);
	Segment create_median(const Point&);
	// Given points lying on side parallel to needed midline
	Segment create_midline(const Point&, const Point&);

	// Create incircle and curcumscribed circle of a triangle
	Circle create_incircle();
	Circle create_circumscribed();
	
	// Function for drawing triangle
	void draw() const override;
	void shift_by_vector(const pair<double, double>& p) override { Vector v = Vector(p.first, p.second); *this = Triangle(A + v, B + v, C + v); }
};

// Check for rectangular triangle
bool rectangular_check(double, double, double);