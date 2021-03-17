#pragma once

struct Color { int R = 0, G = 0, B = 0; };

class Object
{
private:
	Color color = { 0, 0, 0 };
public:
	void set_color(const Color& c) { color = c; }
	Color get_color() const { return color; }
	virtual void draw() const = 0;
};