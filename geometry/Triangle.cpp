#include "Triangle.h"

bool points_check(const Point& A, const Point& B, const Point& C)
{
	Line L(A, B);
	// Check for C in AB Line
	return L.is_on(C);
}

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3) 
{
	A = Point(x1, y1);
	B = Point(x2, y2);
	C = Point(x3, y3);
	init();
}

Triangle::Triangle(const Point &X, const Point &Y, const Point &Z) 
{
	A = X, 
	B = Y, 
	C = Z;
	init();
}

Triangle::Triangle(vector<Point> Arr) 
{
	A = Arr[0],
	B = Arr[1], 
	C = Arr[2];
	init();
}

void Triangle::init() {
	set_sides();
	set_perimeter();
	set_area();
	set_r();
	set_R();
	set_angles();
	set_type();
	set_medians();
	set_bisectors();
	set_heights();
}

void Triangle::set_sides() 
{
	c = dist(A, B);
	a = dist(B, C);
	b = dist(A, C);
}

void Triangle::set_perimeter() 
{
	P = a + b + c;
}

void Triangle::set_area() 
{
	double p = P / 2;
	S = sqrt(p * (p - a) * (p - b) * (p - c));
}

void Triangle::set_angles() 
{
	double pi = 3.1415926535;
	alpha = acos( (b*b + c*c - a*a) / (2*b*c) ) * 180 / pi;
	beta  = acos( (a*a + c*c - b*b) / (2*a*c) ) * 180 / pi;
	gamma = acos( (a*a + b*b - c*c) / (2*a*b) ) * 180 / pi;
}

void Triangle::set_heights() 
{
	hA = (2 * S) / a;
	hB = (2 * S) / b;
	hC = (2 * S) / c;
}

void Triangle::set_R() 
{
	R = (a * b * c) / (4 * S);
}

void Triangle::set_r() 
{
	r = S / (P / 2);
}

void Triangle::set_bisectors() 
{
	double p = P / 2;

	bA = (2 * sqrt(b * c * p * (p - a))) / (b + c);
	bB = (2 * sqrt(a * c * p * (p - b))) / (a + c);
	bC = (2 * sqrt(a * b * p * (p - c))) / (a + b);
}

void Triangle::set_medians() 
{
	mA = 0.5 * sqrt( 2*b*b  + 2*c*c  - a*a);
	mB = 0.5 * sqrt( 2*a*a  + 2*c*c  - b*b);
	mC = 0.5 * sqrt( 2*a*a  + 2*b*b  - c*c);
}

bool rectangular_check(double Alpha, double Beta, double Gamma) 
{
	const double EPS = 1e-4;
	// Check for angle ~ 90 degrees
	return abs(max(max(Alpha, Beta), Gamma) - 90) < EPS;
}

void Triangle::set_type() 
{
	if (rectangular_check(alpha, beta, gamma)) {
		type += "Rectangular";
	}

	else if (alpha > 90 || beta > 90 || gamma > 90) {
		type += "Obtuse-angled";
	}

	else {
		type += "Sharp-angled";
	}

	if (a == b && b == c) {
		type += ", right";
	}

	else if (a == b || b == c || a == c) {
		type += ", isosceles";
	}
}

vector<double> Triangle::get_sides() const
{
	// Returns sides AB, AC, BC
	vector<double> arr = { c, b, a };
	return arr;
}

vector<double> Triangle::get_angles() const 
{
	// Angles in points A, B, C of triangle
	vector<double> arr = { alpha, beta, gamma };
	return arr;
}

vector<double> Triangle::get_altitudes() const 
{
	// Return length of altitude (height) from point A, B, C 
	vector<double> arr = { hA, hB, hC };
	return arr;
}

vector<double> Triangle::get_bisectors() const
{
	// Return length of bisector from point A, B, C
	vector<double> arr = { bA, bB, bC };
	return arr;
}

vector<double> Triangle::get_medians() const
{
	// Return length of median from point A, B, C
	vector<double> arr = { mA, mB, mC };
	return arr;
}

ostream& operator<<(ostream& out, Triangle& triangle) 
{
	// Printing step by step...
	vector<double> arr;
	out << fixed << setprecision(2);
	out << "Type is: " << triangle.get_type() << endl;
	arr = triangle.get_sides();
	out << "AB = " << arr[0] << " AC = " << arr[1] << " BC = " << arr[2] << endl;
	arr = triangle.get_angles();
	out << "Angle in A = " << arr[0] << " B = " << arr[1] << " C = " << arr[2] << endl;
	out << "Perimeter = " << triangle.get_perimeter() << endl;
	out << "Area = " << triangle.get_area() << endl;
	out << "R = " << triangle.get_R() << endl;
	out << "r = " << triangle.get_r() << endl;
	arr = triangle.get_altitudes();
	out << "Length of Altitude from A = " << arr[0] << " B = " << arr[1] << " C = " << arr[2] << endl;
	arr = triangle.get_bisectors();
	out << "Length of Bisector from A = " << arr[0] << " B = " << arr[1] << " C = " << arr[2] << endl;
	arr = triangle.get_medians();
	out << "Length of Median   from A = " << arr[0] << " B = " << arr[1] << " C = " << arr[2] << endl;
	
	return out;
}

int Triangle::point_is_inside(const Point& p) const
{
	/*
	f are results of vector products 
	If fi = 0 we check if points is on the side of our triangle
	If all f > 0 or < 0 then our point is inside the object
	Else points is outside
	*/
	int f1, f2, f3;

	f1 = (A.get_x() - p.get_x()) * (B.get_y() - A.get_y()) - (B.get_x() - A.get_x()) * (A.get_y() - p.get_y());
	f2 = (B.get_x() - p.get_x()) * (C.get_y() - B.get_y()) - (C.get_x() - B.get_x()) * (B.get_y() - p.get_y());
	f3 = (C.get_x() - p.get_x()) * (A.get_y() - C.get_y()) - (A.get_x() - C.get_x()) * (C.get_y() - p.get_y());

	if (f1*f2*f3 == 0) 
	{
		Segment s1(A, B), s2(B, C), s3(A, C);
		if ( s1.is_on(p) || s2.is_on(p) || s3.is_on(p)) {
			return 0;
		}
	}
	else if ((f1 > 0 && f2 > 0 && f3 > 0) || (f1 < 0 && f2 < 0 && f3 < 0)) return 1;
	else return -1;
}

Triangle Triangle::triangle_point_shift1(Point& p1, Point& p2, Point& p3)
{
	if (p2 == A) p1 = B, p3 = C;
	else if (p2 == B) p1 = A, p3 = C;
	else if (p2 == C) p1 = A, p3 = B;
	return Triangle(p1, p2, p3);
}

Triangle Triangle::triangle_point_shift2(Point& p1, Point& p2, Point& p3)
{
	if (p1 == A && p2 == B || p1 == B && p2 == A) p3 = C;
	else if (p1 == A && p2 == C || p1 == C && p2 == A) p3 = B;
	else if (p1 == B && p2 == C || p1 == C && p2 == B) p3 = A;
	return Triangle(p1, p2, p3);
}

Segment Triangle::create_midline(const Point& point1, const Point& point2)
{
	// Same triangle but points will be shifted for formula
	Point p1, p2, p3;
	p1 = point1, p2 = point2;
	Triangle t = triangle_point_shift2(p1, p2, p3);
	
	// Calculate the equation of middle line BC
	Point x1((t.A.get_x() + t.B.get_x()) / 2, (t.A.get_x() + t.B.get_x()) / 2);
	Point x2((t.A.get_x() + t.B.get_x()) / 2, (t.A.get_x() + t.B.get_x()) / 2);
	Segment mid(x1, x2);
	return mid;
}

Segment Triangle::create_altitude(const Point& p)
{
	// Same triangle but points will be shifted for formula
	Point p1, p2, p3;
	p2 = p;
	Triangle t = triangle_point_shift1(p1, p2, p3);

	// Calculate the equation of altitude from B
	// Straight line H height, point h intersection of AC and H 
	Line AC(t.A, t.C);
	Vector np = AC.get_n();
	Line X(t.A, np);
	Line H = make_parallel_line(X, t.B);
	Point h = intersection(AC, H);
	Segment alt(t.B, h);
	return alt;
}

Ray Triangle::create_bisector(const Point& p)
{
	// Same triangle but points will be shifted for formula
	Point p1, p2, p3;
	p2 = p;
	Triangle t = triangle_point_shift1(p1, p2, p3);

	// Calculate the equation of bisector from B
	double l = t.c / t.a;
	//AX = l * XC
	double x = (l * t.C.get_x() + t.A.get_x()) / (1 + l);
	double y = (l * t.C.get_y() + t.A.get_y()) / (1 + l);
	Ray L(t.B, Point(x, y));
	return L;
}

void Triangle::draw() const
{
	glBegin(GL_TRIANGLE_FAN);

	glColor3ub(get_color().R, get_color().G, get_color().B);
	glVertex2d(A.get_x(), A.get_y());
	glVertex2d(B.get_x(), B.get_y());
	glVertex2d(C.get_x(), C.get_y());
	glVertex2d(A.get_x(), A.get_y());

	glEnd();
}