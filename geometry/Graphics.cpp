#include "Graphics.h"

list<Object*> buffer;
list<Object*> deleted_buffer;
list<Point*> point_buffer;
Stack<Object*> stack;

const unsigned char ESC = 27;
const unsigned char ENTER = 13;
const unsigned char BACKSPACE = 8;

const int SHIFT = 10;
const Vector UP_SHIFT = Vector(0, SHIFT);
const Vector DOWN_SHIFT = -UP_SHIFT;
const Vector RIGHT_SHIFT = Vector(10, 0);
const Vector LEFT_SHIFT = -RIGHT_SHIFT;


enum class ENTER_MODE
{
	LINE = 'l',
	SEGMENT = 's',
	RAY = 'r',
	CIRCLE = 'c',
};

int Height = 1080;
int Width = 1920;
Point Center = { Width / 2.0, Height / 2.0 };
ENTER_MODE mode = ENTER_MODE::LINE;

void draw_list()
{
	node<Object*>* p = buffer.get_begin();
	while (p)
	{
		if (p->value->get_color() == Color(0, 0, 0)) p->value->set_color({ rand() % 256, rand() % 256, rand() % 256 });
		if (p == buffer.cur)
			p->value->set_color({ 0, 0, 0 });
		p->value->draw();
		p = p->next;
	}
	node<Point*>* ptr = point_buffer.get_begin();
	while (ptr)
	{
		ptr->value->set_color({ rand() % 256, rand() % 256, rand() % 256 });
		ptr->value->draw();
		ptr = ptr->next;
	}
	while (!stack.is_empty())
	{
		Object* el = stack.top();
		stack.pop();
		el->set_color({ rand() % 256, rand() % 256, rand() % 256 });
		el->draw();
	}
}

void draw_coordinates(int step)
{
	glLineWidth(1);
	for (int x = -1000; x <= 1000; x += step)
	{
		Line Y1 = Line(Point(x, 0), Point(x, step));
		Line X1 = Line(Point(0, x), Point(step, x));
		glColor4b(120, 120, 120, 0.1);
		X1.draw();
		Y1.draw();
	}
	glColor4b(30, 30, 30, 1);
	glLineWidth(5);
	Line X = Line(Point(0, 0), Point(step, 0));
	Line Y = Line(Point(0, 0), Point(0, step));
	X.draw();
	Y.draw();
	glColor4b(0, 0, 0, 1);
}

void draw_function(double(*f)(double x), int step)
{
	Segment* p;
	for (int x = -1000; x < 1000; x += step)
	{
		p = new Segment(Point(x, f(x)), Point(x + step, f(x + step)));
		p->set_color(Color(rand() % 256, rand() % 256, rand() % 256));
		p->draw();
		delete p;
	}
}

double test_func(double x) { return 100 * sin(0.01 * x); }

void Display(void)
{
	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	draw_coordinates();
	draw_list();
	draw_function(test_func);
	glFinish();
}

void Reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-Center.get_x(), Center.get_x(), -Center.get_y(), Center.get_y());
	Height = h;
	Width = w;
	Center.set_x(Width / 2);
	Center.set_y(Height / 2);
}

void test()
{
	stack.push(new Circle(Point(500, 500), 200));
	stack.push(new Line(Point(0, 0), Point(500, 500)));
	stack.push(new Point(200, 100));
	stack.push(new Ray(Point(200, 400), Point(500, 500)));
	stack.push(new Segment(Point(400, 200), Point(500, 500)));
	vector<Point> p = { Point(0, 0), Point(100, 0), Point(200, 200), Point(0, 200) };
	stack.push(new Polygon(p));
	stack.push(new Triangle(Point(500, 500), Point(600, 500), Point(500, 600)));
	stack.push(new Vector(Point(50, 100)));
}

void process_keys(unsigned char key, int x, int y)
{
	if (key == ESC)
		exit(0);
	else if (key == ENTER)
	{
		if (point_buffer.get_size() < 2)
			return;

		if (point_buffer.get_size() == 2)
		{
			try
			{
				if (mode == ENTER_MODE::LINE)
					buffer.push_back(new Line(*point_buffer.pop_front(), *point_buffer.pop_front()));
				else if (mode == ENTER_MODE::RAY)
					buffer.push_back(new Ray(*point_buffer.pop_back(), *point_buffer.pop_back()));
				else if (mode == ENTER_MODE::SEGMENT)
					buffer.push_back(new Segment(*point_buffer.pop_front(), *point_buffer.pop_front()));
				else if (mode == ENTER_MODE::CIRCLE)
				{
					Point center = *point_buffer.pop_front();
					Point second_point = *point_buffer.pop_front();
					double radius = dist(center, second_point);
					buffer.push_back(new Circle(center, radius));
				}
			}
			catch (const exception&)
			{ std::cout << "You can't create an object from two same points!\n"; }
		}
		else if (point_buffer.get_size() == 3)
		{
			Point A = *point_buffer.pop_front();
			Point B = *point_buffer.pop_front();
			Point C = *point_buffer.pop_front();
			try
			{ buffer.push_back(new Triangle(A, B, C)); }
			catch (const exception&)
			{ std::cout << "You can't create this triangle!\n"; }

		}
		else
		{
			size_t n = point_buffer.get_size();
			vector<Point> v(n);
			for (size_t i = 0; i < n; i++)
				v[i] = *point_buffer.pop_front();
			auto last = std::unique(v.begin(), v.end());
			v.erase(last, v.end());
			try
			{ buffer.push_back(new Polygon(v)); }
			catch (const exception&)
			{ std::cout << "You can't create this polygon!\n"; }
		}
	}
	else if (key == 'l' || key == 's' || key == 'r' || key == 'c')
		mode = (ENTER_MODE)key;
	else if (key == '-')
	{
		try
		{ deleted_buffer.push_front(buffer.pop_back()); }
		catch (const exception& ex)
		{ std::cout << "There is no elements in buffer!\n"; }
	}
	else if (key == '=')
	{
		try 
		{ buffer.push_back(deleted_buffer.pop_front()); }
		catch (const exception& ex) 
		{ std::cout << "There is no deleted elements in buffer!\n"; }
	}
	else if (key == 'd')
	{
		if (!buffer.cur)
		{
			if (buffer.get_size() != 0)
				buffer.cur = buffer.get_begin();
		}
		else if (buffer.cur->next)
			buffer.cur = buffer.cur->next;
		else
			buffer.cur = buffer.get_begin();
	}
	else if (key == 'a')
	{
		if (!buffer.cur)
		{
			if (buffer.get_size() != 0)
				buffer.cur = buffer.get_end();
		}
		else if (buffer.cur->last)
			buffer.cur = buffer.cur->last;
		else
			buffer.cur = buffer.get_end();
	}
	else if (key == BACKSPACE)
	{
		try
		{
			Object* val = buffer.pop_node(buffer.cur);
			deleted_buffer.push_front(val);
		}
		catch (const exception& ex)
		{ std::cout << ex.what() << std::endl; }
	}
	glutPostRedisplay();
}

void process_arrows(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		auto p = pair<double, double>(UP_SHIFT.get_x(), UP_SHIFT.get_y());
		buffer.cur->value->shift_by_vector(p);
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		auto p = pair<double, double>(RIGHT_SHIFT.get_x(), RIGHT_SHIFT.get_y());
		buffer.cur->value->shift_by_vector(p);
	}
	else if (key == GLUT_KEY_DOWN)
	{
		auto p = pair<double, double>(DOWN_SHIFT.get_x(), DOWN_SHIFT.get_y());
		buffer.cur->value->shift_by_vector(p);
	}
	else if (key == GLUT_KEY_LEFT)
	{
		auto p = pair<double, double>(LEFT_SHIFT.get_x(), LEFT_SHIFT.get_y());
		buffer.cur->value->shift_by_vector(p);
	}
	glutPostRedisplay();
}

void process_click(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		point_buffer.push_back(new Point(x - Center.get_x(), Height - y - Center.get_y()));
		glutPostRedisplay();
	}
}