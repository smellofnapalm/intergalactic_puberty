#pragma once

#include <stdlib.h>
#include <random>
#include <time.h>
#include "Menu.h"
#include "List.h"
#include "glut/glut.h"
#include "Circle.h"
#include "Line.h"
#include "Polygon.h"
#include "Stack.h"

/* Our functions to deal with objects */

// It draws all objects from the buffer 
// (and all points from point_buffer)
void draw_list();

// This function draws coordinate lines
// With step = 100 (by default)
void draw_coordinates(int step = 100);

// It draw an interpolation of this function
// With step = 10 (by default)
void draw_function(double(*f)(double x), int step = 10);

/*                                    */

/* Here go ordinary GLUT functions */

void Display(void);
void Reshape(GLint w, GLint h);

/*                                 */

/* There we have event handlers (we handl mouse click and keyboard) */

void process_keys(unsigned char key, int x, int y);
void process_click(int button, int state, int x, int y);

/*                                                                  */

/* Test functions */

// Test sin(x) function for draw_function
double test_func(double x);

// Test with hardcoded objects
void test();