#pragma once
#include "Structures.h"

using namespace std;

class ParamsFile
{
public:
	ParamsFile();
	~ParamsFile();

	CameraDefinition cameraDefinition;
	LightPointDefinition lightPointDefinition;
	vector<Sphere> objects;
	PostRenderFilter postRenderFilter;
	Output output;
};

