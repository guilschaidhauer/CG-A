#pragma once
#include "Structures.h"
#include <string>

using namespace std;

class OutputProcessor
{
public:
	OutputProcessor();
	~OutputProcessor();

	virtual void processOutput(string fileName, int w, int h, int dpi, RGBType *data) = 0;
};

