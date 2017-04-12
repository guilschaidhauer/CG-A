#pragma once
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>
#include <utility>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <random>
#include <Windows.h>
#include "Object.h"
#include "Sphere.h"
#include "Camera.h"
#include "Image.h"

using namespace std;

class Render
{
public:
	Render();
	~Render();

	virtual Image* RenderScene(/*vector<Sphere> objects, CameraDefinition camera,*/ int w, int h) = 0;
};

