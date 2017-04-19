#pragma once
#include "Structures.h"
#include "Camera.h"
#include "Sphere.h"
#include <vector>

using namespace std;

class ParamsFile
{
public:
	ParamsFile();
	~ParamsFile();

	Camera cameraDefinition;
	Sphere lightPointDefinition;
	vector<Object*> objects;
	//PostRenderFilter postRenderFilter;
	int width, height;
};

