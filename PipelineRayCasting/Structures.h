#pragma once
#include <vector>
#include "maths_funcs.h"

struct RGBType
{
	float r, g, b;
};

struct Color
{
	float r, g, b;
};

struct CameraDefinition
{
	vec3 position;
	//float ex, ey, ez;
};

struct LightPointDefinition
{
	vec3 position;
	Color color;
};

struct Sphere
{
	float rx, ry, rz;
	float radius;
	Color color;
	vec3 position;
	float refraction;
};

struct PostRenderFilter
{
	float level;
	char type;
};

struct Output
{
	float w, h;
};