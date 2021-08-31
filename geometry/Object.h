#pragma once
using namespace std;

struct Color 
{ 
	int R = 0, G = 0, B = 0; 
	Color(int r, int g, int b) : R(r), G(g), B(b) {}
	Color(int rgb) : R(rgb), G(rgb), B(rgb) {}
	friend bool operator== (const Color& a, const Color& b)
	{ return a.R == b.R && a.G == b.G && a.B == b.B; }
};

class Object
{
protected:
	Color color = { 0, 0, 0 };
	Color line_loop_color = { 50, 50, 50 };
	bool is_filled = true;
public:
	void set_color(const Color& c) { color = c; }
	Color get_color() const { return color; }
	bool get_filled() const { return is_filled; }
	void set_filled(bool _is_filled) { is_filled = _is_filled; }
	Color get_line_loop_color() const { return line_loop_color; }
	void set_line_loop_color(const Color& c) { line_loop_color = c; }
	virtual void draw() const = 0;
	virtual void shift_by_vector(const pair<double, double>&) = 0;
};