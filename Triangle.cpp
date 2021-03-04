#include "Triangle.h"

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3) {

	A = Point(x1, y1);
	B = Point(x2, y2);
	C = Point(x3, y3);

}

Triangle::Triangle(const Point a, const Point b, const Point c) {

	A = a, B = b, C = c;

}

Triangle::Triangle(vector<Point> W) {

	A = W[0], B = W[1], C = W[2];
		
}

void Triangle::set_sides() {

	AB = dist(A, B);
	BC = dist(B, C);
	AC = dist(A, C);

}

bool Triangle::exist_check() {

	return (AB + BC > AC && AB + AC > BC && BC + AC > AB);

}

void Triangle::set_perimetr() {

	P = AB + BC + AC;

}

void Triangle::set_area() {

	double p = P / 2;
	S = sqrt(p * (p - AB) * (p - AC) * (p - BC));

}

void Triangle::set_angles() {

	alpha = asin(BC / (2 * R));
	beta = asin(AC / (2 * R));
	gamma = asin(AB / (2 * R));

}

void Triangle::set_heights() {

	hA = (2 * S) / BC;
	hB = (2 * S) / AC;
	hC = (2 * S) / AB;

}

void Triangle::set_R() {

	R = (AB * BC * AC) / (4 * S);

}

void Triangle::set_r() {

	r = S / (P / 2);

}

void Triangle::set_bisectors() {

	double p = P / 2;

	bA = (2 * sqrt(AC * AB * p * (p - BC))) / (AC + AB);
	bB = (2 * sqrt(BC * AB * p * (p - AC))) / (BC + AB);
	bC = (2 * sqrt(BC * AC * p * (p - AB))) / (BC + AC);


}

void Triangle::set_medians() {

	mA = 0.5 * sqrt(2 * AC * AC + 2 * AB * AB - BC * BC);
	mB = 0.5 * sqrt(2 * BC * BC + 2 * AB * AB - AC * AC);
	mC = 0.5 * sqrt(2 * BC * BC + 2 * AC * AC - AB * AB);


}

void Triangle::set_type() {

	if (alpha > 90 || beta > 90 || gamma > 90) {
		type += "Тупоугольный";
	}
	else if (alpha == 90 || beta == 90 || gamma == 90) {
		type += "Прямоугольный";
	}
	else {
		type += "Остроугольный";
	}

	if (AC == BC == AB) {
		type += ", правильный";
	}


}

double Triangle::get_area() const {

	return S;

}

double Triangle::get_perimetr() const {

	return P;

}

vector<double> Triangle::get_sides() const {

	vector<double> A = { BC, AC, AB };
	return A;

}

vector<double> Triangle::get_angles() const {

	vector<double> A = { alpha, beta, gamma };
	return A;

}

vector<double> Triangle::get_heights() const {

	vector<double> A = { hA, hB, hC };
	return A;

}

double Triangle::get_R() const {

	return R;

}

double Triangle::get_r() const {

	return r;

}

string Triangle::get_type() const {

	return type;

}

vector<double> Triangle::get_bisectors() const {

	vector<double> A = { bA, bB, bC };
	return A;

}

vector<double> Triangle::get_medians() const {

	vector<double> A = { mA, mB, mC };
	return A;

}

void output(Triangle& triangle) {

	if (!triangle.exist_check()) {
		cout << "Your triangle doesn't exist! Try again!";
		return;
	}

	cout << "Type is: " << triangle.get_type() << endl;
	auto arr = triangle.get_sides();
	cout << "AB = " << arr[0] << " AC = " << arr[1] << " BC = " << arr[2] << endl;
	auto arr = triangle.get_angles();
	cout << "Angles in A = " << arr[0] << " B = " << arr[1] << " C = " << arr[2] << endl;
	cout << "Perimetr = " << triangle.get_perimetr() << endl;
	cout << "Area = " << triangle.get_area() << endl;
	cout << "R = " << triangle.get_R() << endl;
	cout << "r = " << triangle.get_r() << endl;
	auto arr = triangle.get_heights();
	cout << "Height from A = " << arr[0] << " B = " << arr[1] << " C = " << arr[2];
	auto arr = triangle.get_bisectors();
	cout << "Bisector from A = " << arr[0] << " B = " << arr[1] << " C = " << arr[2];
	auto arr = triangle.get_medians();
	cout << "Median from A = " << arr[0] << " B = " << arr[1] << " C = " << arr[2];

}

void Triangle::create_triangle() {

	cout << "You are creating the Triangle.";
	Point A, B, C;
	cout << endl << "Input point А: ";
	cin >> A;
	cout << endl << "Input point B: ";
	cin >> B;
	cout << endl << "Input point C: ";
	cin >> C;

	Triangle triangle(A, B, C);
	output(triangle);

}