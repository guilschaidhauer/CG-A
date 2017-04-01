#include "RayCasting.h"



RayCasting::RayCasting()
{
}


RayCasting::~RayCasting()
{
}


Image* RayCasting::RenderScene(/*vector<Sphere> objects, CameraDefinition camera,*/ int w, int h)
{
	Image* image = new Image(w, h);

	return image;
}