#include "Point.h"
class Line
{
protected:
	// Normalized coef of the line
	double A = 0, B = 0, C = 0;

	// Initial point
	Point p0 = { 0, 0 };

	// Normalized (of length 1) directing vector (v) and normal vector (n)
	Vector v = { 1, 0 }, n = {0, 1};
public:
	Line() {}
	Line(double, double, double);
	Line(const Point&, const Point&);
	Line(const Point&, const Vector&);

	void set_p0();
	void set_v();
	void set_n();
	void set_coef();

	double get_A() const { return A; };
	double get_B() const { return B; };
	double get_C() const { return C; };
	Point get_p0() const { return p0; };
	Vector get_v() const { return v; };
	Vector get_n() const { return n; };

	// If line(x, y): Ax + By + C = 0, than line[x] = y
	double operator[] (double);

	// <!> I don't know how to implement different ways
	// <!> to actually input the line, so I've chosen the simplest
	// <!> one for users - to enter two points
	friend istream& operator>> (istream&, Line&);

	friend ostream& operator<< (ostream&, const Line&);
};