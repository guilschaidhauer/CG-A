#pragma once
#include <iostream>
#include <math.h>
#include "Image.h"
#include "Intersection.h"
#include "Structures.h"

using namespace std;

class Render
{
public:
	Render();
	~Render();

	virtual Image* RenderScene(/*vector<Sphere> objects, CameraDefinition camera,*/ int w, int h) = 0;
};

