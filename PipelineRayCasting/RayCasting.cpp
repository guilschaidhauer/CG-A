#include "RayCasting.h"



RayCasting::RayCasting()
{
}
//Test

RayCasting::~RayCasting()
{
}

float clamp(const float &lo, const float &hi, const float &v)
{
	return max(lo, min(hi, v));
}

float deg2rad(const float &deg)
{
	return deg * M_PI / 180;
}

Vec3f mix(const Vec3f &a, const Vec3f& b, const float &mixValue)
{
	return a * (1 - mixValue) + b * mixValue;
}

float mix(const float &a, const float &b, const float &mix)
{
	return b * mix + a * (1 - mix);
}


Image* RayCasting::RenderScene(/*vector<Sphere> objects, CameraDefinition camera,*/ int w, int h)
{
	Image* image = new Image(w, h);

	return image;
}