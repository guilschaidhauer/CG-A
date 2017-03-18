#pragma once
#include <iostream>
#include <math.h>
#include "Render.h"

using namespace std;

class RayCasting : public Render
{
public:
	RayCasting();
	~RayCasting();

	void RenderScene(vector<Sphere> objects, CameraDefinition camera, float w, float h) override;
};

