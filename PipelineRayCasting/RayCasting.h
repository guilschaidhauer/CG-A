#pragma once
#include "Render.h"

using namespace std;

class RayCasting : public Render
{
public:
	RayCasting();
	~RayCasting();

	Image* RenderScene(vector<Object*> objects, Camera camera, int w, int h) override;

	int MAX_DEPTH;
};

