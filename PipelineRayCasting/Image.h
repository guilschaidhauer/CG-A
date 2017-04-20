#pragma once
#include <stdio.h>
#include <fstream>
#include <string>
#include "Structures.h"
#include <vector>
#include "lodepng.h"
#pragma warning(disable:4996)
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
	//RGBType *pixels;
	std::vector<unsigned char> pixels;
	int w;
	int h;
	int dpi;
};

//class ImagePNG
//{
//public:
//	ImagePNG(int width, int height);
//	~ImagePNG();
//
//	void saveImage(string fileName);
//	//RGBType *pixels;
//	std::vector<unsigned char> pixels;
//	int w;
//	int h;
//	//int dpi;
//};
