#pragma once

#include "polygon.h"
const vector<string> v =
{
	"Create a new point",
	"Create a new line",
	"Create a new triange",
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