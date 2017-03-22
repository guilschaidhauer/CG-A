#include "RayCasting.h"



RayCasting::RayCasting()
{
}


RayCasting::~RayCasting()
{
}


Image* RayCasting::RenderScene(vector<Sphere> objects, CameraDefinition camera, int w, int h)
{
	float raySize = 15;

	//possivel codigo:

	Image* image = new Image(w, h);
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			Ray ray = ConstructRayThroughPixel(camera, i, j, w, h);
			//Intersection hit = FindIntersection(ray, scene);
			//image->setPixel(GetColor(hit), i, j);
		}
	}
	return image;
}

//Image size should not be passed here
Ray RayCasting::ConstructRayThroughPixel(CameraDefinition camera, int x, int y, int imageWidth, int imageHeight) {

	//These should not be definded here
	float fov = 60;
	float M_PI = 3.1415;

	float imageAspectRatio = imageWidth / (float)imageHeight; // assuming width > height 
	float Px = (2 * ((x + 0.5) / imageWidth) - 1) * tan(fov / 2 * M_PI / 180) * imageAspectRatio;
	//Added ) at the end
	float Py = (1 - 2 * ((y + 0.5) / imageHeight) * tan(fov / 2 * M_PI / 180));
	vec3 rayOrigin(camera.position);
	vec3 rayDirection = vec3(Px, Py, -1) - rayOrigin; // note that this just equal to Vec3f(Px, Py, -1); 
	rayDirection = normalise(rayDirection);
	Ray newRay(rayOrigin, rayDirection);
	return newRay;
}