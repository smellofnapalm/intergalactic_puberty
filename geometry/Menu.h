#pragma once

#include <vector>
#include <string>
#include <conio.h>
#include "List.h"
using namespace std;

const vector<string> v =
{
	"Create a new point",
	"Create a new line",
	"Create a new triangle",
	"Create a new circle",
	"Create a new polygon"
};

template<class T>
void create_point(list<T>&);
template<class T>
void create_line(list<T>&);
template<class T>
void create_triangle(list<T>&);
template<class T>
void create_circle(list<T>&);
template<class T>
void create_polygon(list<T>&);

int print_menu(vector<string> mas = v);
template<class T>
void menu(list<T>&);
template<class T>
void menu_triangle(list<T>&, list<T>&);
template<class T>
void menu_polygon(list<T>&, list<T>&);
template<class T>
void menu_point_line(list<T>&, Point*&, Line*&);

#include "Polygon.h"
#include "Triangle.h"
#include "Line.h"
#include "Circle.h"
#include "Menu.h"
#include "List.h"
#include <iostream>

template<class T>
void create_point(list<T>& buffer)
{
	int x, y;
	cout << endl;
	cout << "Please, enter the coordinates of the point\n";
	cin >> x >> y;
	Point p = Point(x, y);
	cout << p << endl;

	p.set_color({ 100, 100, 100 });
	buffer.push_back(p);
}

template<class T>
void create_line(list<T>& buffer)
{
	Point p0, p1;
	cout << "Enter two points of the line:\n";
	cin >> p0 >> p1;
	Line l;
	try
	{
		l = Line(p0, p1);
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
		return;
	}
	cout << l;

	l.set_color({ 100, 100, 100 });
	buffer.push_back(l);
}

template<class T>
void create_triangle(list<T>& buffer)
{
	cout << "You are creating the Triangle." << endl;
	Point A, B, C;
	cout << "Input point A: ";
	cin >> A;
	cout << "Input point B: ";
	cin >> B;
	cout << "Input point C: ";
	cin >> C;

	if (points_check(A, B, C))
	{
		cout << endl << "ERROR: THREE DOTS ON THE SAME LINE IS ILLEGAL!" << endl;
		return;
	}

	Triangle triangle(A, B, C);
	cout << triangle;

	triangle.set_color({ 100, 100, 100 });
	triangle.draw();
}

template<class T>
void create_circle(list<T>& buffer)
{
	Point center;
	double r, S, L;
	cout << "Enter the center of the circle" << endl;
	cin >> center;
	cout << "Enter radius of the circle" << endl;
	cin >> r;
	Circle circle;
	try
	{
		circle = Circle(center, r);
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
		return;
	}
	cout << circle;
	S = circle.get_area();
	L = circle.get_length();
	cout << "Circumference length = " << L << endl << "Area of a circle = " << S << endl;

	circle.set_color({ 100, 100, 100 });
	circle.draw();
}

template<class T>
void create_polygon(list<T>& buffer)
{
	int n;
	cout << endl;
	cout << "Enter the number of points of a polygon: ";
	cin >> n;
	vector <Point> points(n);
	cout << "Now enter the coordinates of points in the correct order\n";
	for (int i = 0; i < n; i++)
		cin >> points[i];
	Polygon polygon;
	try
	{
		polygon = Polygon(points);
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
		return;
	}
	cout << polygon;

	polygon.set_color({ 100, 100, 100 });
	polygon.draw();
}

int print_menu(vector<string> mas)
{
	const int ENTER = 224;
	const int UP = 72;
	const int DOWN = 80;
	const int ESC = 27;
	const int CR = 13;

	int N = mas.size();
	int key = 0, move;
	while (true)
	{
		cout << "Choose a menu item you need:\n\n";
		cout << "Press ESC to quit\n";
		for (int i = 0; i < N; i++)
		{
			if (i != key)
				cout << i + 1 << ". " << mas[i] << endl;
			else
				cout << "\x1B[34m" << i + 1 << ". " << mas[i] << "\033[0m\n";
		}
		cout << '\n';

		move = _getch();
		if (move == ESC)
		{
			system("cls");
			return N + 1;
		}
		if (move == ENTER)
			move = _getch();

		if (move == CR)
		{
			system("cls");
			return key;
		}
		else if (move == UP)
			key = ((key - 1) % N + N) % N;
		else if (move == DOWN)
			key = (key + 1) % N;
		system("cls");
	}
	return key;
}

template<class T>
void menu(list<T>& buffer)
{
	while (true)
	{
		int key = print_menu();
		if (key == 0) create_point(buffer);
		else if (key == 1) create_line(buffer);
		else if (key == 2) create_triangle(buffer);
		else if (key == 3) create_circle(buffer);
		else if (key == 4) create_polygon(buffer);
		else return;

		char x;
		cout << "Do you want to continue? (y/n):\n";
		cin >> x;
		if (x == 'y')
			system("cls");
		else
			return;
	}

}

template<class T>
void menu_triangle(list<T>& l, list<T>& buf)
{
	Triangle* t = dynamic_cast<Triangle*>(l.cur->value);
	while (true)
	{
		const vector<string> v =
		{
			"Make height 1", "Make height 2", "Make height 3",
			"Make bisector 1", "Make bisector 2", "Make bisector 3",
			"Make midline 1", "Make midline 2", "Make midline 3",
			"Make median 1", "Make median 2", "Make median 3",
			"Create incircle", "Add one more object",
			"Exit"
		};
		int key = print_menu(v);
		if (key == 0) l.push_back(new Segment(t->create_altitude(t->getA())));
		else if (key == 1) l.push_back(new Segment(t->create_altitude(t->getB())));
		else if (key == 2) l.push_back(new Segment(t->create_altitude(t->getC())));
		else if (key == 3) l.push_back(new Ray(t->create_bisector(t->getA())));
		else if (key == 4) l.push_back(new Ray(t->create_bisector(t->getB())));
		else if (key == 5) l.push_back(new Ray(t->create_bisector(t->getC())));
		else if (key == 6) l.push_back(new Segment(t->create_midline(t->getB(), t->getC())));
		else if (key == 7) l.push_back(new Segment(t->create_midline(t->getA(), t->getC())));
		else if (key == 8) l.push_back(new Segment(t->create_midline(t->getA(), t->getB())));
		else if (key == 9) l.push_back(new Segment(t->create_median(t->getA())));
		else if (key == 10) l.push_back(new Segment(t->create_median(t->getB())));
		else if (key == 11) l.push_back(new Segment(t->create_median(t->getC())));
		else if (key == 12) l.push_back(new Circle(t->create_incircle()));
		else if (key == 13) buf.push_back(t);
		else return;

		char x;
		cout << "Do you want to continue? (y/n):\n";
		cin >> x;
		if (x == 'y')
			system("cls");
		else
			return;
	}
}

template<class T>
void menu_polygon(list<T>& l, list<T>& buf)
{
	Polygon* p = dynamic_cast<Polygon*>(l.cur->value);
	size_t n = p->get_points().size();
	vector<string> v;
	for (size_t i = 1; i <= n; i++)
		v.push_back("Make bisector " + to_string(i));
	v.push_back("Rotate polygon for alpha degrees");
	v.push_back("Add one more object");
	v.push_back("Exit");
	while (true)
	{
		int key = print_menu(v);
		if (key < n) l.push_back(new Ray(p->create_bisector(p->operator[](key))));
		else if (key == n)
		{
			cout << "Enter degrees (from 0 to 360):\n";
			double alpha;
			cin >> alpha;
			alpha *= (PI / 180);
			p->rotate_polygon(alpha, p->get_center());
		}
		else if (key == n + 1) buf.push_back(p);
		else return;

		char x;
		cout << "Do you want to continue? (y/n):\n";
		cin >> x;
		if (x == 'y')
			system("cls");
		else
			return;
	}
}

template<class T>
void menu_point_line(list<T>& l, Point*& point, Line*& line)
{
	while (true)
	{
		const vector<string> v =
		{
			"Make parallel line",
			"Make perpendicular line",
			"Check halfplane",
			"Exit"
		};
		int key = print_menu(v);
		if (key == 0) l.push_back(new Line(make_parallel_line(*line, *point)));
		else if (key == 1) l.push_back(new Line(make_perpendicular_line(*line, *point)));
		else if (key == 2)
		{
			int check = line->check_halfplane(*point);
			if (check == 1) cout << "Point is above the line!\n";
			else if (check == 0) cout << "Point is on the line!\n";
			else if (check == -1) cout << "Point is beneath the line!\n";
		}
		else return;

		char x;
		cout << "Do you want to continue? (y/n):\n";
		cin >> x;
		if (x == 'y')
			system("cls");
		else
			return;
	}
}