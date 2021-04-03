#pragma once

#include <vector>
using namespace std;

const vector<string> v =
{
	"Create a new point",
	"Create a new line",
	"Create a new triangle",
	"Create a new circle",
	"Create a new polygon"
};

void create_point();
void create_line();
void create_triangle();
void create_circle();
void create_polygon();

int print_menu(vector<string> mas = v);
void menu();