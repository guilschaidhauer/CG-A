#include "RayCasting.h"



RayCasting::RayCasting()
{
}


RayCasting::~RayCasting()
{
}


Image* RayCasting::RenderScene(vector<Sphere> objects, CameraDefinition camera, int w, int h)
{
	const Vec3 white(255, 255, 255);
	const Vec3 black(0, 0, 0);
	const Vec3 red(255, 0, 0);

	const Sphere sphere(Vec3(w*0.5, h*0.5, 50), 50);
	const Sphere light(Vec3(0, 0, 50), 1);

	double t;
	Vec3 pix_col(black);

	Image* image = new Image(w, h);

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			pix_col = black;

			const Ray ray(Vec3(x, y, 0), /*Use camera*/Vec3(0, 0, 1));
			if (sphere.intersect(ray, t)) {
				const Vec3 pi = ray.o + ray.d*t;
				const Vec3 L = light.c - pi;
				const Vec3 N = sphere.getNormal(pi);
				const double dt = dot(L.normalize(), N.normalize());

				pix_col = (red + white*dt) * 0.5;
				clamp255(pix_col);
				image->setPixel(pix_col, y, x);
			}
		}
	}




	/*float raySize = 15;

	//possivel codigo:

	Image* image = new Image(w, h);
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			Ray ray = ConstructRayThroughPixel(camera, i, j, w, h);
			Intersection hit = FindIntersection(ray, objects);
			//image->setPixel(GetColor(hit), i, j);

			RGBType color;
			color.r = 255;
			color.g = 255;
			color.b = 0;

			image->setPixel(color, i, j);
		}
	}
	*/
	return image;
}

Intersection RayCasting::FindIntersection(Ray ray, vector<Sphere> scene)
{
	for (int i = 0; i < scene.size(); i++) {

	}

	return Intersection();
}

RGBType RayCasting::GetColor(Intersection hit)
{
	return RGBType();
}

//Image size should not be passed here
/*
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
*/