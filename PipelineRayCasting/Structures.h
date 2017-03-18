#pragma once
#include <vector>

struct Position
{
	float x, y, z;
};

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
	float ex, ey, ez;
};

struct LightPointDefinition
{
	Position position;
	Color color;
};

struct Sphere
{
	float rx, ry, rz;
	float radius;
	Color color;
	Position position;
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