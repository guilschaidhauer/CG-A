#pragma once
#include "Image.h"
#include "Color.h"
#include <math.h>
#include <windows.h>

class Filter{
public:
	Filter();
	~Filter();
	virtual void doIt(Image*);
	float bias = 0, factor = 0;
	int filterHeight = 3, filterWidth = 3;
	double matrix[3][3];
};