#pragma once

#include <vector>
#include <string>
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