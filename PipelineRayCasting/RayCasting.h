#pragma once
#include "Render.h"

using namespace std;

class RayCasting : public Render
{
public:
	RayCasting();
	~RayCasting();

	Image* RenderScene(vector<Sphere> objects, CameraDefinition camera, int w, int h) override;

	Ray ConstructRayThroughPixel(CameraDefinition camera, int x, int y, int imageWidth, int imageHeight);
};

