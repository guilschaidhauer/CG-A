#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include "Image.h"
#include "Intersection.h"
#include "Structures.h"
#include "Color.h"
#include "Vect.h"
#include "Color.h"
#include "Object.h"
#include "Source.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"

using namespace std;

class Render
{
public:
	Render();
	~Render();

	virtual Image* RenderScene(vector<Sphere> objects, Camera camera, int w, int h) = 0;
};

