#include "polygon.h"
ifstream in;
const string path1 = "input1.txt";
const string path2 = "input2.txt";
const string path3 = "input3.txt";
const vector<string> v =
{
	"Create a new point",
	"Create a new line",
	"Create a new triange",
	"Create a new circle",
	"Create a new polygon"
};

void create_point()
{
	int x, y;
	cout << endl;
	cout << "Please, enter the coordinates of the point\n";
	cin >> x >> y;
	Point p = Point(x, y);
	cout << p << endl;
}

void create_line()
{
	// TO DO
}

void create_triangle()
{
	// TO DO
}

void create_circle()
{
	// TO DO
}

void create_polygon()
{
	int n;
	cout << endl;
	cout << "Enter the number of points of a polygon: ";
	cin >> n;
	vector <Point> points(n);
	cout << "Now enter the coordinates of points in the correct order\n";
	for (int i = 0; i < n; i++)
		cin >> points[i];
	auto polygon = Polygon(points);
	cout << polygon;
}

int print_menu(vector<string> mas = v)
{
	int N = mas.size();
	int key = 0, move;
	while (true)
	{
		cout << "Choose a menu item you need:\n\n";
		cout << "Press ESC to quit¸\n";
		for (int i = 0; i < N; i++)
		{
			if (i != key)
				cout << i + 1 << ". " << mas[i] << endl;
			else
				cout << "\x1B[34m" << i + 1 << ". " << mas[i] << "\033[0m\n";
		}
		cout << '\n';

		move = _getch();
		if (move == 27)
		{
			system("cls");
			return N + 1;
		}
		if (move == 224)
			move = _getch();

		if (move == 13)
		{
			system("cls");
			return key;
		}
		else if (move == 72)
			key = ((key - 1) % N + N) % N;
		else if (move == 80)
			key = (key + 1) % N;
		system("cls");
	}
	return key;
}

void menu()
{
	while (true)
	{
		int key = print_menu();
		if (key == 0) create_point();
		else if (key == 1) create_line();
		else if (key == 2) create_triangle();
		else if (key == 3) create_circle();
		else if (key == 4) create_polygon();
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



