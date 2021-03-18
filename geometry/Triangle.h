#pragma once

#include "Point.h"

class Triangle : public Object
{

protected:

	Point A, B, C;

	double a, b, c, S, P; 
	//altitudes
	double hA, hB, hC; 
	//medians
	double mA, mB, mC; 
	//bisectors
	double bA, bB, bC; 
	//in A, B, C
	double alpha, beta, gamma; 
	double r, R;

	string type = "";

public:

	Triangle(double, double, double, double, double, double);
	Triangle(const Point &, const Point &, const Point &);
	Triangle(vector<Point>);

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

	string get_type() const;
	double get_area() const;
	double get_perimeter() const;
	double get_R() const;
	double get_r() const;

	vector<double> get_medians() const;
	vector<double> get_sides() const;
	vector<double> get_angles() const;
	vector<double> get_heights() const;
	vector<double> get_bisectors() const;
	
	bool point_is_inside(const Point&);
	
	friend ostream& operator<<(ostream&, Triangle&);
	friend bool rectangular_check(double Alpha, double Beta, double Gamma);

	void draw() const override;
};