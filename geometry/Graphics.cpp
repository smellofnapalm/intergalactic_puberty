#include "Graphics.h"
#include "Menu.h"
#include <set>
#include <typeinfo>

/*                      GLOBAL BUFFERS OF OBJECTS                          */

// Buffer of all objects on the scene
list<Object*> buffer;

// Buffer of all deleted objects (that are not drawn)
list<Object*> deleted_buffer;

// Buffer of points, which user enters by clicking to create a new object
// (Actually it behaves like stack, so in future it migrate from list to stack)
list<Point*> point_buffer;

// Just a test stack, we don't use it in real work
Stack<Object*> stack;

// List of objects we use for menu
list<Object*> menu_buffer;

/*                                                                          */

// Global scaling factor to zoom in or out 
double scale = 1.0;
/*                       USEFUL CONSTANTS                                   */

// These are just consts for buttons
const unsigned char ESC = 27;
const unsigned char ENTER = 13;
const unsigned char BACKSPACE = 8;
const unsigned char CTRL_Z = 26;
const unsigned char CTRL_Y = 25;

// We have an ability to move objects
// And SHIFT is used for choosing how many pixels we move an object
const int SHIFT = 10;
const Vector UP_SHIFT = Vector(0, SHIFT);
const Vector DOWN_SHIFT = -UP_SHIFT;
const Vector RIGHT_SHIFT = Vector(SHIFT, 0);
const Vector LEFT_SHIFT = -RIGHT_SHIFT;
/*                                                                           */

// ENTER_MODE is used to define which object is created by 2 points right now
enum class ENTER_MODE
{
	LINE = 'l',
	SEGMENT = 's',
	RAY = 'r',
	CIRCLE = 'c',
};

// Height and Width of screen 
// It works only on FULL-HD monitors!!!
int Height = 1080;
int Width = 1920;

// Center of the coordinates
Point Center = { Width / 2.0, Height / 2.0 };

// Current enter mode
ENTER_MODE mode = ENTER_MODE::LINE;

void draw_list()
{
	node<Object*>* p = buffer.get_begin();
	while (p)
	{
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
	if (buffer.cur)
	{
		p = buffer.cur;
		bool filled = p->value->get_filled();
		Color c = p->value->get_color();
		if (c == Color(0, 0, 0)) c = Color(rand() % 256, rand() % 256, rand() % 256);
		p->value->set_color({ 0, 0, 0 });
		p->value->set_filled(true);
		p->value->draw();
		p->value->set_filled(filled);
		p->value->set_color(c);
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
	for (int x = -1000*scale; x <= 1000*scale; x += step)
	{
		Line Y1 = Line(Point(x, 0), Point(x, scale*Height));
		Line X1 = Line(Point(0, x), Point(scale*Width, x));
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
		p = new Segment(Point(x, f(x)), Point(double(x) + double(step), f(double(x) + double(step))));
		p->set_color(Color(rand() % 256, rand() % 256, rand() % 256));
		p->draw();
		delete p;
	}
}

double test_func(double x) { return 100 * sin(0.01 * x); }

void Display(void)
{
	glMatrixMode(GL_PROJECTION);

	// Do this scaling thing after every Redisplay call
	glLoadIdentity();
	gluOrtho2D(-Center.get_x() * scale, Center.get_x() * scale, -Center.get_y() * scale, Center.get_y() * scale);

	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draws the grid
	draw_coordinates();

	// Draws all objects from out buffer
	draw_list();

	glFinish();
}

void Reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);

	// Some magic with scaling (zoom in or out)
	glLoadIdentity();
	gluOrtho2D(-Center.get_x()*scale, Center.get_x()*scale, -Center.get_y()*scale, Center.get_y()*scale);

	Height = h;
	Width = w;
	Center.set_x(Width / 2);
	Center.set_y(Height / 2);
}

void test()
{
	// Some hardcoded objects to test the stack. I don't know why we need it, if we have list already :(
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

void process_enter()
{
	// Call the menu for current object
	if (point_buffer.get_size() == 0)
	{
		if (!buffer.cur) return;

		string type = typeid(*buffer.cur->value).name();
		if (menu_buffer.get_size() == 0)
		{
			if (type == "class Triangle")
				menu_triangle(buffer, menu_buffer);
			else if (type == "class Polygon")
				menu_polygon(buffer, menu_buffer);
			else if (type == "class Segment")
			{
				Segment* s = dynamic_cast<Segment*>(buffer.cur->value);
				buffer.push_back(new Line(s->segment_bisection()));
				menu_buffer.push_back(buffer.cur->value);
				cout << "Segment bisector has been built and segment was added to the menu buffer!\n";
			}
			else
			{
				menu_buffer.push_back(buffer.cur->value);
				cout << "Object has been added to the menu buffer!\n";
			}
		}
		else if (menu_buffer.get_size() == 1)
		{
			if (buffer.cur->value == menu_buffer.get_begin()->value)
			{
				cout << "You can't work with two same objects!\n";
				return;
			}
			string type1 = typeid(*menu_buffer.get_begin()->value).name();

			if ((type == "class Point" && (type1 == "class Line" || type1 == "class Segment" || type1 == "class Ray"))
				|| ((type == "class Line" || type == "class Segment" || type == "class Ray") && type1 == "class Point"))
			{
				Line* l;
				Point* p;
				if (dynamic_cast<Line*>(menu_buffer.get_begin()->value))
				{
					l = dynamic_cast<Line*>(menu_buffer.get_begin()->value);
					p = dynamic_cast<Point*>(buffer.cur->value);
				}
				else
				{
					l = dynamic_cast<Line*>(buffer.cur->value);
					p = dynamic_cast<Point*>(menu_buffer.get_begin()->value);
				}
				menu_point_line(buffer, p, l);
			}
			else if ((type == "class Line" && type1 == "class Line")
				|| (type == "class Ray" && type1 == "class Ray")
				|| (type == "class Segment" && type1 == "class Segment"))
			{
				Line* l = dynamic_cast<Line*>(menu_buffer.get_begin()->value);
				Line* l1 = dynamic_cast<Line*>(buffer.cur->value);
				if (are_parallel(*l, *l1)) cout << "Lines are parallel!\n";
				else
				{
					Point p;
					if (type == "class Line") p = intersection(*l, *l1);
					else if (type == "class Ray")
					{
						Ray* r = dynamic_cast<Ray*>(menu_buffer.get_begin()->value);
						Ray* r1 = dynamic_cast<Ray*>(buffer.cur->value);
						p = ray_intersection(*r, *r1);
						if (p == UNDEF) cout << "Intersection point doesn't exist!\n";
					}
					else if (type == "class Segment")
					{
						Segment* s = dynamic_cast<Segment*>(menu_buffer.get_begin()->value);
						Segment* s1 = dynamic_cast<Segment*>(buffer.cur->value);
						p = segment_intersection(*s, *s1);
						if (p == UNDEF) cout << "Intersection point doesn't exits!\n";
					}

					if (p != UNDEF)
					{
						cout << "Intersection point is (" << p.get_x() << ", " << p.get_y() << ")\n";
						buffer.push_back(new Point(p));
					}
				}
			}
			else if (type == "class Circle" && type1 == "class Circle")
			{
				Circle* c = dynamic_cast<Circle*>(menu_buffer.get_begin()->value);
				Circle* c1 = dynamic_cast<Circle*>(buffer.cur->value);
				vector<Point> v = circles_intersection(*c, *c1);
				if (v.size() == 0) cout << "Circles don't intersect!\n";
				else if (v.size() == 1)
				{
					cout << "Circles touch at one point!\n";
					cout << "This point is(" << v[0].get_x() << ", " << v[0].get_y() << ")\n";
					buffer.push_back(new Point(v[0]));
				}
				else if (v.size() == 2)
				{
					cout << "Circles intersect at two points!\n";
					cout << "The first point is " << v[0] << endl;
					cout << "The secon point is " << v[1] << endl;
					buffer.push_back(new Point(v[0]));
					buffer.push_back(new Point(v[1]));
				}
			}
			else if ((type == "class Point" && type1 == "class Circle")
				|| (type == "class Circle" && type1 == "class Point"))
			{
				Point* p;
				Circle* c;
				if (type == "class Point")
				{
					p = dynamic_cast<Point*>(buffer.cur->value);
					c = dynamic_cast<Circle*>(menu_buffer.get_begin()->value);
				}
				else
				{
					p = dynamic_cast<Point*>(menu_buffer.get_begin()->value);
					c = dynamic_cast<Circle*>(buffer.cur->value);
				}
				int x = c->point_occurrence(*p);
				if (x == 1)
					cout << "Point is inside the circle and you can't make tangent line!\n";
				else if (x == 0)
				{
					cout << "Point is on the circle and you can make a tangent line!\n";
					Line line = Circle::make_tangent_line(*c, *p)[0];
					buffer.push_back(new Line(line));
				}
				else if (x == -1)
				{
					cout << "Point is out of the circle and we have 2 tangent lines!\n";
					vector<Line> v = Circle::make_tangent_line(*c, *p);
					buffer.push_back(new Line(v[0]));
					buffer.push_back(new Line(v[1]));
					cout << "Distance from the point to the circle is " << c->distance_to_point(*p) << endl;
				}
			}
			menu_buffer.pop_node(menu_buffer.get_begin());
			cout << "Now menu buffer is empty!\n";

		}
	}
	// Create a point (and delete the last point from point_buffer)
	else if (point_buffer.get_size() == 1) 
		buffer.push_back(new Point(*point_buffer.pop_back()));
	// We have many objects that we can create with 2 points
	// So it depends on the ENTER_MODE, that the user choose
	// By default it is LINE
	else if (point_buffer.get_size() == 2)
	{
		try
		{
			if (mode == ENTER_MODE::LINE)
				buffer.push_back(new Line(*point_buffer.pop_back(), *point_buffer.pop_back()));
			else if (mode == ENTER_MODE::RAY)
				buffer.push_back(new Ray(*point_buffer.pop_back(), *point_buffer.pop_back()));
			else if (mode == ENTER_MODE::SEGMENT)
				buffer.push_back(new Segment(*point_buffer.pop_back(), *point_buffer.pop_back()));
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
	// By 3 points we can only create a triangle
	else if (point_buffer.get_size() == 3)
	{
		Point A = *point_buffer.pop_front();
		Point B = *point_buffer.pop_front();
		Point C = *point_buffer.pop_front();
		try
		{ buffer.push_back(new Triangle(A, B, C)); }
		catch (const exception&)
		{ cout << "You can't create this triangle!\n"; }
	}
	else
	{
		size_t n = point_buffer.get_size();
		set<Point> s;
		vector<Point> v;
		// We want to work with only unique points (and only convex objects)
		for (size_t i = 0; i < n; i++) s.insert(*point_buffer.pop_front());
		for (const auto& point : s) v.push_back(point);
		v = Polygon::convex_hull(v);
		Polygon::delete_bad_points(v);
		// If it is actually a triangle
		if (v.size() == 3)
		{
			try
			{ buffer.push_back(new Triangle(v[0], v[1], v[2])); }
			catch (const exception&)
			{ cout << "You can't create this triangle!\n"; }
		}
		// Or it is a segment
		else if (v.size() == 2)
		{
			try
			{ buffer.push_back(new Segment(v[0], v[1])); }
			catch (const exception&)
			{ cout << "You can't create this segment!"; }
		}
		// Or it is just a point
		else if (v.size() == 1)
			buffer.push_back(new Point(v[0]));
		else
		{
			try
			{ buffer.push_back(new Polygon(v)); }
			catch (const exception&)
			{ cout << "You can't create this polygon!\n"; }
		}
	}

	// I want random color to be bright (because selection color is black)
	Color random_color = Color(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55);
	if (buffer.get_end()) 
		buffer.get_end()->value->set_color(random_color);
}

void process_keys(unsigned char key, int x, int y)
{
	// Close the whole program
	if (key == ESC)
		exit(0);
	// Create an object or call a menu for a current object if point_buffer is empty
	else if (key == ENTER)
		process_enter();
	// Process keys 'l', 's', 'r' and 'c' in any possible way
	else if
		(key == 'l' || key == 'L' || key == (unsigned char)'ä' || key == (unsigned char)'Ä'
			|| key == 's' || key == 'S' || key == (unsigned char)'û' || key == (unsigned char)'Û'
			|| key == 'r' || key == 'R' || key == (unsigned char)'ê' || key == (unsigned char)'Ê'
			|| key == 'c' || key == 'C' || key == (unsigned char)'ñ' || key == (unsigned char)'Ñ')
	{
		if (key == (unsigned char)'ä' || key == (unsigned char)'Ä' || key == 'L') key = 'l';
		else if (key == (unsigned char)'û' || key == (unsigned char)'Û' || key == 'S') key = 's';
		else if (key == 'R' || key == (unsigned char)'ê' || key == (unsigned char)'Ê') key = 'r';
		else if (key == 'C' || key == (unsigned char)'ñ' || key == (unsigned char)'Ñ') key = 'c';
		mode = (ENTER_MODE)key;
	}
	// Delete last added object from the scene
	else if (key == CTRL_Z)
	{
		try
		{ 
			Object* last_object = buffer.pop_back();
			// It deleted object is in menu, then delete it from menu
			if (menu_buffer.get_size() == 1 && last_object == menu_buffer.get_begin()->value)
				menu_buffer.pop_node(menu_buffer.get_begin());
			deleted_buffer.push_front(buffer.pop_back()); 
		}
		catch (const exception&)
		{ std::cout << "There is no elements in buffer!\n"; }
	}
	// Return the last deleted object to the scene
	else if (key == CTRL_Y)
	{
		try
		{ buffer.push_back(deleted_buffer.pop_front()); }
		catch (const exception&)
		{ std::cout << "There is no deleted elements in buffer!\n"; }
	}
	// Move the current pointer to the right (key 'D')
	else if (key == 'd' || key == 'D' || key == (unsigned char)'â' || key == (unsigned char)'Â')
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
	// Move the current pointer to the left (key 'A')
	else if (key == 'a' || key == 'A' || key == (unsigned char)'ô' || key == (unsigned char)'Ô')
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
	// Delete the current object from the scene
	else if (key == BACKSPACE)
	{
		try
		{
			Object* val = buffer.pop_node(buffer.cur);
			// It current object is in menu, delete it from menu also
			if (menu_buffer.get_size() == 1 && val == menu_buffer.get_begin()->value)
				menu_buffer.pop_node(menu_buffer.get_begin());
			deleted_buffer.push_front(val);
			buffer.cur = nullptr;
		}
		catch (const exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
	// Fill or do not fill the current object
	else if (key == 'f' || key == 'F' || key == (unsigned char)'à' || key == (unsigned char)'À')
	{
		if (buffer.cur == nullptr) return;
		Object* obj = buffer.cur->value;
		bool is_filled = obj->get_filled();
		obj->set_filled(!is_filled);
	}
	// Zoom out (hardcoded restriction to zoom more than in 32 times - begin problems with graphics)
	else if (key == '-') { if (scale >= 32) return;  scale *= 2; }
	// Zoom in (problems begin even with smaller scales)
	else if (key == '=') { if (scale <= 1.0 / 4) return; scale /= 2; }
	else {}
	glutPostRedisplay();
}

void process_arrows(int key, int x, int y)
{
	if (buffer.cur == nullptr) return;
	// Move the current object UP
	if (key == GLUT_KEY_UP)
	{
		auto p = pair<double, double>(UP_SHIFT.get_x(), UP_SHIFT.get_y());
		buffer.cur->value->shift_by_vector(p);
	}
	// Move the current object RIGHT
	else if (key == GLUT_KEY_RIGHT)
	{
		auto p = pair<double, double>(RIGHT_SHIFT.get_x(), RIGHT_SHIFT.get_y());
		buffer.cur->value->shift_by_vector(p);
	}
	// Move the current object DOWN
	else if (key == GLUT_KEY_DOWN)
	{
		auto p = pair<double, double>(DOWN_SHIFT.get_x(), DOWN_SHIFT.get_y());
		buffer.cur->value->shift_by_vector(p);
	}
	// Move the current object LEFT
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
		point_buffer.push_back(new Point(scale*(x - Center.get_x()), scale*(Height - y - Center.get_y())));
		glutPostRedisplay();
	}
}