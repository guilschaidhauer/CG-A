#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Structures.h"

using namespace std;

struct RGBType {
	double r;
	double g;
	double b;
};

class Image
{
public:
	Image(int width, int height);
	~Image();

	void saveImage(string fileName);
	void setPixel(double r, double g, double b, int x, int y);

	RGBType *pixels;

	int w;
	int h;
	int dpi;
};

