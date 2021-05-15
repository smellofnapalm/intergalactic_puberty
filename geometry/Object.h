#pragma once

struct Color 
{ 
	int R = 0, G = 0, B = 0; 
	Color(int r, int g, int b) : R(r), G(g), B(b) {}
	friend bool operator== (const Color& a, const Color& b)
	{ return a.R == b.R && a.G == b.G && a.B == b.B; }
};

class Object
{
protected:
	Color color = { 0, 0, 0 };
public:
	void set_color(const Color& c) { color = c; }
	Color get_color() const { return color; }
	virtual void draw() const = 0;
};