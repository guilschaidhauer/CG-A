#pragma once
#include "Structures.h"

using namespace std;

class Render
{
public:
	Render();
	~Render();

	virtual void RenderScene(vector<Sphere> objects, CameraDefinition camera, float w, float h) = 0;

	RGBType *pixels;
};

