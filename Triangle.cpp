#include "Triangle.h"

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3) 
{
	A = Point(x1, y1);
	B = Point(x2, y2);
	C = Point(x3, y3);

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

Triangle::Triangle(const Point &X, const Point &Y, const Point &Z) 
{
	A = X, B = Y, C = Z;

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

Triangle::Triangle(vector<Point> Arr) 
{
	A = Arr[0], B = Arr[1], C = Arr[2];

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

double Triangle::get_area() const 
{
	return S;
}

double Triangle::get_perimeter() const 
{
	return P;
}

double Triangle::get_R() const
{
	return R;
}

double Triangle::get_r() const
{
	return r;
}

string Triangle::get_type() const
{
	return type;
}

vector<double> Triangle::get_sides() const
{
	vector<double> Arr = { c, b, a };
	return Arr;
}

vector<double> Triangle::get_angles() const 
{
	vector<double> Arr = { alpha, beta, gamma };
	return Arr;
}

vector<double> Triangle::get_heights() const 
{
	vector<double> Arr = { hA, hB, hC };
	return Arr;
}

vector<double> Triangle::get_bisectors() const
{
	vector<double> Arr = { bA, bB, bC };
	return Arr;
}

vector<double> Triangle::get_medians() const
{
	vector<double> Arr = { mA, mB, mC };
	return Arr;
}

ostream& operator<<(ostream& out, Triangle& triangle) 
{
	out << fixed << setprecision(2);
	out << "Type is: " << triangle.get_type() << endl;
	vector<double> arr = triangle.get_sides();
	out << "AB = " << arr[0] << " AC = " << arr[1] << " BC = " << arr[2] << endl;
	arr = triangle.get_angles();
	out << "Angles in A = " << arr[0] << " B = " << arr[1] << " C = " << arr[2] << endl;
	out << "Perimeter = " << triangle.get_perimeter() << endl;
	out << "Area = " << triangle.get_area() << endl;
	out << "R = " << triangle.get_R() << endl;
	out << "r = " << triangle.get_r() << endl;
	arr = triangle.get_heights();
	out << "Length of Altitude from A = " << arr[0] << " B = " << arr[1] << " C = " << arr[2] << endl;
	arr = triangle.get_bisectors();
	out << "Length of Bisector from A = " << arr[0] << " B = " << arr[1] << " C = " << arr[2] << endl;
	arr = triangle.get_medians();
	out << "Length of Median   from A = " << arr[0] << " B = " << arr[1] << " C = " << arr[2] << endl;
	
	return out;
}

bool Triangle::Point_is_inside(const Point& P)
{
	//�������� �� ����
	bool f1, f2, f3;

	Point X = A;
	Point Y = B;
	Point Z = C;

	f1 = (X.get_x() - P.get_x()) * (Y.get_y() - X.get_y()) - (Y.get_x() - X.get_x()) * (X.get_y() - P.get_y()) >= 0;
	f2 = (Y.get_x() - P.get_x()) * (Z.get_y() - Y.get_y()) - (Z.get_x() - Y.get_x()) * (Y.get_y() - P.get_y()) >= 0;
	f3 = (Z.get_x() - P.get_x()) * (X.get_y() - Z.get_y()) - (X.get_x() - Z.get_x()) * (Z.get_y() - P.get_y()) >= 0;

	return f1 && f2 && f3;
}
