#pragma once

#include "Point.h"

class Line : public Object
{
protected:
	// Normalized coef of the line
	double A = 0, B = 0, C = 0;

	// Initial point
	Point p0 = { 0, 0 };

	// Normalized (of length 1) directing vector (v) and normal vector (n)
	Vector v = { 1, 0 }, n = {0, 1};

	// They do init, not set, that's why they are private
	void set_p0();
	void set_v();
	void set_n();
	void set_coef();
public:
	Line() {}
	Line(double, double, double);
	Line(const Point&, const Point&);
	Line(const Point&, const Vector&);

	double get_A() const { return A; };
	double get_B() const { return B; };
	double get_C() const { return C; };
	Point get_p0() const { return p0; };
	Vector get_v() const { return v; };
	Vector get_n() const { return n; };

	// If line(x, y): Ax + By + C = 0, than line[x] = y
	double operator[] (double) const;
	// <!> I don't know how to implement different ways
	// <!> to actually input the line, so I've chosen the simplest
	// <!> one for users - to enter two points
	friend istream& operator>> (istream&, Line&);
	friend ostream& operator<< (ostream&, const Line&);
	friend bool operator==(const Line&, const Line&);

	friend bool are_parallel(const Line&, const Line&);
	friend Line make_parallel_line(const Line&, const Point&);
	friend Point intersection(const Line&, const Line&);

	// Check if the Point on the Line
	virtual bool is_on(const Point&) const;

	// Funcation value f(x, y) = Ax + By + C
	double function_value(const Point&);

	// Find in which half-plane the point lies (with respect to certain line)
	// Returns 1 if the point is in the positive half-plane (where normal vector points)
	// Return 0 if the point is on the line
	// Return -1 if the point is in the negative half-plane
	int check_halfplane(const Point&);

	void draw() const override;
	void shift_by_vector(const pair<double, double>& p) override { Vector w = Vector(p.first, p.second); *this = Line(p0 + w, v); }
};

class Ray : public Line
{
protected:
	// The point from needed half of the line
	Point p1 = { 0, 0 };
public:
	Ray() {}
	Ray(const Line&, const Point&, const Point&);
	Ray(const Point&, const Point&);

	friend istream& operator>> (istream&, Ray&);
	friend ostream& operator<< (ostream&, const Ray&);

	friend Point ray_intersection(const Ray&, const Ray&);

	// Check if the Point is on the Ray
	bool is_on(const Point&) const override;

	void draw() const override;
	void shift_by_vector(const pair<double, double>& p) override { Vector v = Vector(p.first, p.second); *this = Ray(p0 + v, p1 + v); }
};

class Segment : public Line
{
protected:
	// Right end point of the segment
	Point p1 = { 0, 0 };

	// The middle of the segment
	Point avr_point = { 0, 0 };
public:
	Segment() {}
	Segment(const Line&, const Point&, const Point&);
	Segment(const Point&, const Point&);

	Point get_p1() const { return p1; }
	Point get_avr() const { return avr_point; }

	friend istream& operator>> (istream&, Segment&);
	friend ostream& operator<< (ostream&, const Segment&);

	friend Point segment_intersection(const Segment&, const Segment&);

	// Check if the Point is on the Segment
	bool is_on(const Point&) const override;

	void draw() const override;
	void shift_by_vector(const pair<double, double>& p) override { Vector v = Vector(p.first, p.second); *this = Segment(p0 + v, p1 + v); }
};