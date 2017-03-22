#pragma once
#include <stdio.h>
#include <fstream>
#include <string>
#include "Structures.h"

using namespace std;

class Image
{
public:
	Image(int width, int height);
	~Image();

	void saveImage(string fileName);

	void setPixel(RGBType color, int w, int h);

	int w;
	int h;
	int dpi;
	RGBType* pixels;
};

