#include "RayCasting.h"



RayCasting::RayCasting()
{
}


RayCasting::~RayCasting()
{
}


void RayCasting::RenderScene(vector<Sphere> objects, CameraDefinition camera, float w, float h)
{
	float raySize = 15;

	//TODO implement raycasting here

	/*Sphere sphere = objects[0];

	for (int i = 0; i < h; i++) 
	{
		for (int j = 0; j < w; j++)
		{
			Position directionVector;
			directionVector.x = j - camera.ex;
			directionVector.y = i - camera.ey;
			directionVector.z = 0;

			Position rayEndPoint;
			rayEndPoint.x = camera.ex + (raySize * directionVector.x);
			rayEndPoint.y = camera.ey + (raySize * directionVector.y);
			rayEndPoint.z = camera.ez + (raySize * directionVector.z);

			float a = pow(rayEndPoint.x - camera.ex, 2) + pow(rayEndPoint.y - camera.ey, 2) + pow(rayEndPoint.z - camera.ez, 2);
			float b = 2 * ((rayEndPoint.x - camera.ex)*(rayEndPoint.x - sphere.rx) + (rayEndPoint.y - camera.ey)*(camera.ey - sphere.ry) + (rayEndPoint.z - camera.ez) * (camera.ez - sphere.rz));
			float c = pow(camera.ex - sphere.rx, 2) + pow(camera.ey - sphere.ry, 2) + pow(camera.ez - sphere.rz, 2) - pow(sphere.radius, 2);

			float delta = pow(b, 2) - 4 * a * c;

			if (delta < 0)
			{
				cout << "no interaction" << endl;
			}
			else
			{
				cout << "THERE IS INTERACTION" << endl;
			}
		}
	}*/


	//possivel codigo:

	//Image* image = new Image(width, height);
	//for (int i = 0; i < width; i++) {
	//	for (int j = 0; j < height; j++) {
	//		Ray ray = ConstructRayThroughPixel(camera, i, j);
	//		Intersection hit = FindIntersection(ray, scene);
	//		image->setPixel(GetColor(hit), i, j);
	//	}
	//}
	//return image;
}

//possivel codigo:
//
//
//Ray Raycasting::ConstructRayThroughPixel(Camera camera, int x, int y) {
//
//	float imageAspectRatio = imageWidth / (float)imageHeight; // assuming width > height 
//	float Px = (2 * ((x + 0.5) / imageWidth) - 1) * tan(fov / 2 * M_PI / 180) * imageAspectRatio;
//	float Py = (1 - 2 * ((y + 0.5) / imageHeight) * tan(fov / 2 * M_PI / 180);
//	vec3 rayOrigin(camera.position);
//	vec3 rayDirection = vec3(Px, Py, -1) - rayOrigin; // note that this just equal to Vec3f(Px, Py, -1); 
//	rayDirection = normalise(rayDirection);
//	Ray newRay(rayOrigin, rayDirection);
//	return newRay;
//}