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
	camera.z = 30;

	camera.ortho.xi = 0.0;
	camera.ortho.xf = 10.0;
	camera.ortho.yi = 0.0;
	camera.ortho.yf = 10.0;

	float celulaX = (camera.ortho.xf - camera.ortho.xi) / w;
	float celulaY = (camera.ortho.yf - camera.ortho.yi) / h;

	const Vec3 white(255, 255, 255);
	const Vec3 black(0, 0, 0);

	const Sphere light(Vec3(0, 0, -200), 1, white);

	double t;
	Vec3 pix_col(black);

	Image* image = new Image(w, h);

	for (int x = 0; x < w; ++x) {
		for (int y = 0; y < h; ++y) {

			//Vec3 pontoNaGrid(camera.ortho.yf - y*celulaY, camera.ortho.xi + x*celulaX, 0.0);

			pix_col = black;
			image->setPixel(pix_col, x, y);

			//Ray ray = ConstructRayThroughPixel(camera, pontoNaGrid.x, pontoNaGrid.y, w, h);
			Ray ray = ConstructRayThroughPixel(camera, y, x, w, h);

			for (int i = 0; i < objects.size(); i++) {
				if (objects.at(i).intersect(ray, t)) {
					/*const Vec3 pi = ray.o + ray.d*t;
					const Vec3 L = light.c - pi;
					const Vec3 N = objects.at(i).getNormal(pi);
					const double dt = dot(L.normalize(), N.normalize());

					pix_col = (objects.at(i).color + white*dt) * 0.5;*/
					pix_col = objects.at(i).color;
					//clamp255(pix_col);
					image->setPixel(pix_col, x, y);
				}
			}
		}
	}

	return image;
}

Ray RayCasting::ConstructRayThroughPixel(CameraDefinition camera, int x, int y, int imageWidth, int imageHeight) {
	
	Vec3 rayOrigin(Vec3(camera.x, camera.y, camera.z));
	Vec3 rayDirection = Vec3(x, y, 0) - rayOrigin;
	rayDirection = rayDirection.normalize();

	Ray newRay(rayOrigin, rayDirection);
	return newRay;
}