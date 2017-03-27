#include "RayCasting.h"



RayCasting::RayCasting()
{
}


RayCasting::~RayCasting()
{
}


Image* RayCasting::RenderScene(vector<Sphere> objects, CameraDefinition camera, int w, int h)
{
	camera.x = w*0.5;
	camera.y = h*0.5;
	camera.z = 200;

	const Vec3 white(255, 255, 255);
	const Vec3 black(0, 0, 0);
	//const Vec3 red(255, 0, 0);

	//const Sphere sphere(Vec3(w*0.5, h*0.5, -10), 50);
	const Sphere light(Vec3(0, 0, 50), 1, white);

	double t;
	Vec3 pix_col(black);

	Image* image = new Image(w, h);

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			pix_col = black;

			//Aqui ele tá construindo um raio do pixel da tela reto
			//const Ray ray(Vec3(x, y, 0), Vec3(0, 0, 1));

			//TODO temos que fazer ele criar um raio da camera, passando por cada pixel. Mais ou menos como tá nessa funcão. Mas por algum motivo não funciona.
			//TODO quando for tentar colocar essa função, olhar a posição da camera e dos objetos, pode ser que elas estajam erradas.
			Ray ray = ConstructRayThroughPixel(camera, x, y, w, h);

			for (int i = 0; i < objects.size(); i++) {
				if (objects.at(i).intersect(ray, t)) {
					const Vec3 pi = ray.o + ray.d*t;
					const Vec3 L = light.c - pi;
					const Vec3 N = objects.at(i).getNormal(pi);
					const double dt = dot(L.normalize(), N.normalize());

					pix_col = (objects.at(i).color + white*dt) * 0.5;
					clamp255(pix_col);
					image->setPixel(pix_col, y, x);
				}
			}
		}
	}

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

Ray RayCasting::ConstructRayThroughPixel(CameraDefinition camera, int x, int y, int imageWidth, int imageHeight) {
	
	Vec3 rayOrigin(Vec3(camera.x, camera.y, camera.z));
	Vec3 rayDirection = Vec3(x, y, 0) - rayOrigin; // note that this just equal to Vec3f(Px, Py, -1); 
	rayDirection = rayDirection.normalize();

	Ray newRay(rayOrigin, rayDirection);
	return newRay;
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
	Vec3 rayOrigin(Vec3(camera.x, camera.y, camera.z));
	Vec3 rayDirection = Vec3(Px, Py, -1) - rayOrigin; // note that this just equal to Vec3f(Px, Py, -1); 
	rayDirection = rayDirection.normalize();

	//Vec3 rayDirection(0, 0, 1);

	Ray newRay(rayOrigin, rayDirection);
	return newRay;
}
*/