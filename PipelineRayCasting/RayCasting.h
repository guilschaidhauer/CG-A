#pragma once
#include "Render.h"

using namespace std;

class RayCasting : public Render
{
public:
	RayCasting();
	~RayCasting();

	Image* RenderScene(vector<Sphere> objects, CameraDefinition camera, int w, int h) override;

	Ray ConstructRayThroughPixel(CameraDefinition camera, int x, int y, int z, int imageWidth, int imageHeight);

	void clamp255(Vec3& col) {
		col.x = (col.x > 255) ? 255 : (col.x < 0) ? 0 : col.x;
		col.y = (col.y > 255) ? 255 : (col.y < 0) ? 0 : col.y;
		col.z = (col.z > 255) ? 255 : (col.z < 0) ? 0 : col.z;
	}

};

