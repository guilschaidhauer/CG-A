#pragma once
#include "maths_funcs.h"
class Ray
{
public:
	Ray();
	Ray(vec3 orig, vec3 dir);
	~Ray();
private:
	vec3 direction;
	vec3 origin;
};

