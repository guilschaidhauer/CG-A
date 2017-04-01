#pragma once
#include <vector>
#include "Sphere.h"
#include "Camera.h"

using namespace std;

struct Output {
	int w, h;
};

class ParamsFile
{
public:
	ParamsFile();
	~ParamsFile();

	vector<Sphere> objects;
	Output output;
	Camera camera;
};

