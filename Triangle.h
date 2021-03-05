#pragma once

#include "Point.h"

class Triangle
{

protected:

	Point A, B, C;

	double AB, BC, AC, S, P; 
	double hA, hB, hC; //heights
	double mA, mB, mC; //medians
	double bA, bB, bC; //bisectors
	double alpha, beta, gamma; //in A,B,C
	double r, R;

	string type = "";

public:

	Triangle(double, double, double, double, double, double);
	Triangle(const Point, const Point, const Point);
	Triangle(vector<Point>);

	bool exist_check();

	void set_area();
	void set_perimetr();
	void set_sides();
	void set_angles();
	void set_heights();
	void set_R();
	void set_r();
	void set_bisectors();
	void set_medians();
	void set_type();

	string get_type() const;
	double get_area() const;
	double get_perimetr() const;
	double get_R() const;
	double get_r() const;

	vector<double> get_medians() const;
	vector<double> get_sides() const;
	vector<double> get_angles() const;
	vector<double> get_heights() const;
	vector<double> get_bisectors() const;

};

void output(Triangle& triangle);
void create_triangle();