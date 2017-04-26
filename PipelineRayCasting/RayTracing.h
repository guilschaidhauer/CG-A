#pragma once
#include "Render.h"

using namespace std;

class RayTracing : public Render
{
public:
	RayTracing();
	~RayTracing();

	Image* RenderScene(vector<Object*> objects, Camera camera, int w, int h);

	int MAX_DEPTH;
};

