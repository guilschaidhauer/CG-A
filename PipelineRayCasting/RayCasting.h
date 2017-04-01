#pragma once
#include "Render.h"
#include <time.h>
//#include "Color.h"

using namespace std;

class RayCasting : public Render
{
public:
	RayCasting();
	~RayCasting();

	Image* RenderScene(vector<Sphere> objects, Camera camera, int w, int h) override;

};

