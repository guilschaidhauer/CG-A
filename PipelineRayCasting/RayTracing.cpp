#include "RayTracing.h"

float MAX_DEPTH = 3;

RayTracing::RayTracing()
{
}

RayTracing::~RayTracing()
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

void fresnel(const Vec3f &I, const Vec3f &N, const float &ior, float &kr)
{
	float cosi = clamp(-1, 1, I.dotProduct(N));
	float etai = 1, etat = ior;
	if (cosi > 0) { std::swap(etai, etat); }
	// Compute sini using Snell's law
	float sint = etai / etat * sqrtf(max(0.f, 1 - cosi * cosi));
	// Total internal reflection
	if (sint >= 1) {
		kr = 1;
	}
	else {
		float cost = sqrtf(max(0.f, 1 - sint * sint));
		cosi = fabsf(cosi);
		float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		kr = (Rs * Rs + Rp * Rp) / 2;
	}
	// As a consequence of the conservation of energy, transmittance is given by:
	// kt = 1 - kr;
}

Vec3f trace(
	const Vec3f &rayorig,
	const Vec3f &raydir,
	const std::vector<Object*> objects,
	const int &depth)
{

	Vec3f background_color = Vec3f(1,1,1);
	//if (raydir.length() != 1) std::cerr << "Error " << raydir << std::endl;
	float tnear = INFINITY;
	Object* sphere = nullptr;
	// find intersection of this ray with the sphere in the scene
	for (unsigned i = 0; i < objects.size(); ++i) {
		float t0 = INFINITY, t1 = INFINITY;
		if (objects[i]->intersect(rayorig, raydir, t0, t1)) {
			if (t0 < 0) t0 = t1;
			if (t0 < tnear) {
				tnear = t0;
				sphere = objects[i];
			}
		}
	}
	// if there's no intersection return black or background color

	if (!sphere) 
		return background_color;

	Vec3f surfaceColor = 0; // color of the ray/surfaceof the object intersected by the ray
	Vec3f intersection = rayorig + raydir * tnear; // point of intersection
	Vec3f normal;
	Vec2f tex;
	sphere->getSurfaceData(intersection, normal, tex); // normal at the intersection point
	normal.normalize(); // normalize normal direction
					  // If the normal and the view direction are not opposite to each other
					  // reverse the normal direction. That also means we are inside the sphere so set
					  // the inside bool to true. Finally reverse the sign of IdotN which we want
					  // positive.
	float bias = 0.01;//1e-4; // add some bias to the point from which we will be tracing
	bool inside = false;
	if (raydir.dotProduct(normal) > 0) {
		normal = -normal, inside = true;
	}
	
	if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_DEPTH) {
		float facingratio = -raydir.dotProduct(normal);
		// change the mix value to tweak the effect
		float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
		//fresnel(intersection, normal, 1.3, fresneleffect);
		// compute reflection direction (not need to normalize because all vectors
		// are already normalized)
		Vec3f refldir = raydir - normal * 2 * raydir.dotProduct(normal);
		refldir.normalize();
		Vec3f reflection = trace(intersection + normal * bias, refldir, objects, depth + 1);
		Vec3f refraction = 0;
		// if the sphere is also transparent compute refraction ray (transmission)
		if (sphere->transparency) {
			float ior = 1.1, eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
			float cosi = -normal.dotProduct(raydir);
			float k = 1 - eta * eta * (1 - cosi * cosi);
			Vec3f refrdir = raydir * eta + normal * (eta *  cosi - sqrt(k));
			refrdir.normalize();
			refraction = trace(intersection - normal * bias, refrdir, objects, depth + 1);
		}
		// Replaction + refraction
		surfaceColor = (
			reflection * fresneleffect +
			refraction * (1 - fresneleffect) * sphere->transparency) * sphere->surfaceColor;
	}
	else {
		// It's diffuse. Stop raytracing
		for (unsigned i = 0; i < objects.size(); ++i) {
			if (objects[i]->emissionColor.x > 0) {
				// this is a light
				Vec3f transmission = 1;
				Vec3f lightDirection = dynamic_cast<Sphere*> (objects[i])->getSphereCenter() - intersection;
				lightDirection.normalize();
				for (unsigned j = 0; j < objects.size(); ++j) {
					if (i != j) {
						float t0, t1;
						if (objects[j]->intersect(intersection + normal * bias, lightDirection, t0, t1)) {
							transmission = 0;
							break;
						}
					}
				}
				//Vec3f temp;
				//temp.doSum(sphere->surfaceColor * transmission *
				//	max(float(0), nhit.dotProduct(lightDirection)) * objects[i]->emissionColor);
				surfaceColor = surfaceColor + (sphere->surfaceColor * transmission *
					max(float(0), normal.dotProduct(lightDirection)) * objects[i]->emissionColor);
				//surfaceColor += (sphere->surfaceColor * transmission *
				//	max(float(0), nhit.dotProduct(lightDirection)) * objects[i]->emissionColor);
			}
		}
	}

	return surfaceColor + sphere->emissionColor;
}

Vec3f castRay(
	const Vec3f &orig, const Vec3f &dir,
	const std::vector<Object*> objects)
{
	Vec3f hitColor = 0;
	const Object *hitObject = nullptr; // this is a pointer to the hit object
	return trace(orig, dir, objects, 0);
}

void render(
	const std::vector<Object*> objects, Camera camera, int w, int h, Image *image)
{
	Vec3f *framebuffer = new Vec3f[w * h];
	Vec3f *pix = framebuffer;
	float scale = tan(deg2rad(camera.FOV() * 0.5));
	float imageAspectRatio = w / (float)h;
	Vec3f orig;
	camera.cameraToWorld().multVecMatrix(Vec3f(0, 0, 10), orig);
	Vec3f value = 0;
	for (int j = 0; j < h; ++j) {
		for (int i = 0; i < w; ++i) {
			float x = (2 * (i + 0.5) / (float)w - 1) * imageAspectRatio * scale;
			float y = (1 - 2 * (j + 0.5) / (float)h) * scale;


			Vec3f dir;
			camera.cameraToWorld().multDirMatrix(Vec3f(x, y, -1), dir);
			dir.normalize();
			*(pix++) = castRay(orig, dir, objects);
			//fprintf(stderr, "\r%3d%c", int(j / (float)h * 100), '%');
		}
	}

	for (int x = 0; x < w; ++x) {
		for (int y = 0; y < h; ++y) {
			int index = 4 * w * y + 4 * x;
			char r = (char)(255 * clamp(0, 1, framebuffer[x + y*w].x));
			char g = (char)(255 * clamp(0, 1, framebuffer[x + y*w].y));
			char b = (char)(255 * clamp(0, 1, framebuffer[x + y*w].z));
			image->pixels[index + 0] = r;
			image->pixels[index + 1] = g;
			image->pixels[index + 2] = b;
			image->pixels[index + 3] = 255;
		}
	}

	delete[] framebuffer;
}


Image* RayTracing::RenderScene(vector<Object*> objects, Camera camera, int w, int h)
{
	Image* image = new Image(w, h);

	const float kInfinity = INFINITY;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	int width = w, height = h;
	//render
	render(objects, camera, width, height, image);

	return image;
}