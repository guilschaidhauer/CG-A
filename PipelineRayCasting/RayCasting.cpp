#include "RayCasting.h"



RayCasting::RayCasting()
{
}

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

Vec3f trace(
	const Vec3f &rayorig,
	const Vec3f &raydir,
	const std::vector<Object*> objects,
	const int &depth)
{
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

	if (!sphere) return Vec3f(2);
	Vec3f surfaceColor = 0; // color of the ray/surfaceof the object intersected by the ray
	Vec3f phit = rayorig + raydir * tnear; // point of intersection
	Vec3f nhit;
	Vec2f tex;
	sphere->getSurfaceData(phit, nhit, tex); // normal at the intersection point
	nhit.normalize(); // normalize normal direction
					  // If the normal and the view direction are not opposite to each other
					  // reverse the normal direction. That also means we are inside the sphere so set
					  // the inside bool to true. Finally reverse the sign of IdotN which we want
					  // positive.
	float bias = 1e-4; // add some bias to the point from which we will be tracing
	bool inside = false;
	if (raydir.dotProduct(nhit) > 0) nhit = -nhit, inside = true;
	if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < 3/*TODO USE MAX DEPTH INSTEAD*/) {
		float facingratio = -raydir.dotProduct(nhit);
		// change the mix value to tweak the effect
		float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
		// compute reflection direction (not need to normalize because all vectors
		// are already normalized)
		Vec3f refldir = raydir - nhit * 2 * raydir.dotProduct(nhit);
		refldir.normalize();
		Vec3f reflection = trace(phit + nhit * bias, refldir, objects, depth + 1);
		Vec3f refraction = 0;
		// if the sphere is also transparent compute refraction ray (transmission)
		if (sphere->transparency) {
			float ior = 1.1, eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
			float cosi = -nhit.dotProduct(raydir);
			float k = 1 - eta * eta * (1 - cosi * cosi);
			Vec3f refrdir = raydir * eta + nhit * (eta *  cosi - sqrt(k));
			refrdir.normalize();
			refraction = trace(phit - nhit * bias, refrdir, objects, depth + 1);
		}
		// the result is a mix of reflection and refraction (if the sphere is transparent)
		surfaceColor = (
			reflection * fresneleffect +
			refraction * (1 - fresneleffect) * sphere->transparency) * sphere->surfaceColor;
	}
	else {
		// it's a diffuse object, no need to raytrace any further
		for (unsigned i = 0; i < objects.size(); ++i) {
			if (objects[i]->emissionColor.x > 0) {
				// this is a light
				Vec3f transmission = 1;
				Vec3f lightDirection = dynamic_cast<Sphere*> (objects[i])->getSphereCenter() - phit;
				lightDirection.normalize();
				for (unsigned j = 0; j < objects.size(); ++j) {
					if (i != j) {
						float t0, t1;
						if (objects[j]->intersect(phit + nhit * bias, lightDirection, t0, t1)) {
							transmission = 0;
							break;
						}
					}
				}
				//Vec3f temp;
				//temp.doSum(sphere->surfaceColor * transmission *
				//	max(float(0), nhit.dotProduct(lightDirection)) * objects[i]->emissionColor);
				surfaceColor = surfaceColor + (sphere->surfaceColor * transmission *
					max(float(0), nhit.dotProduct(lightDirection)) * objects[i]->emissionColor);
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
	float t; // this is the intersection distance from the ray origin to the hit point
			 //if (TTrace(orig, dir, objects, t, hitObject)) {
			 //       Vec3f Phit = orig + dir * t;
			 //       Vec3f Nhit;
			 //       Vec2f tex;
			 //       hitObject->getSurfaceData(Phit, Nhit, tex);
			 //        //Use the normal and texture coordinates to shade the hit point.
			 //        //The normal is used to compute a simple facing ratio and the texture coordinate
			 //        //to compute a basic checker board pattern
			 //       float scale = 4;
			 //       float pattern = (fmodf(tex.x * scale, 1) > 0.5) ^ (fmodf(tex.y * scale, 1) > 0.5);
			 //	hitColor = max(0.f, Nhit.dotProduct(-dir)) * mix(hitObject->getColor(), hitObject->getColor() * 0.8, pattern);
			 //   }

	return trace(orig, dir, objects, 0);
}

void render(
	const std::vector<Object*> objects, Camera camera, int w, int h, Image *image)
{
	Vec3f *framebuffer = new Vec3f[w * h];
	Vec3f *pix = framebuffer;
	float scale = tan(deg2rad(camera.FOV() * 0.5));
	float imageAspectRatio = w / (float)h;
	// [comment]
	// Don't forget to transform the ray origin (which is also the camera origin
	// by transforming the point with coordinates (0,0,0) to world-space using the
	// camera-to-world matrix.
	// [/comment]
	Vec3f orig;
	camera.cameraToWorld().multVecMatrix(Vec3f(0, 0, 10), orig);
	Vec3f value = 0;
	for (int j = 0; j < h; ++j) {
		for (int i = 0; i < w; ++i) {

			//
			//	for (float fragmenty = h; fragmenty < h + 1.0f; fragmenty += 0.5f)
			//		for (float fragmentx = w; fragmentx < w + 1.0f; fragmentx += 0.5f) {
			//	{
			//			//	fragmenty = fragmenty > h ? h : fragmenty;
			//				//fragmentx = fragmentx > w ? w : fragmentx;
			//		float x = (2 * (fragmenty + 0.5) / (float)w - 1) * imageAspectRatio * scale;
			//		float y = (1 - 2 * (fragmentx + 0.5) / (float)h) * scale;
			//		// [comment]
			//		// Don't forget to transform the ray direction using the camera-to-world matrix.
			//		// [/comment]
			//		Vec3f dir;
			//		camera.cameraToWorld().multDirMatrix(Vec3f(x, y, -1), dir);
			//		dir.normalize();
			//		
			//		value = value + castRay(orig, dir, objects);
			//		

			//	}
			//}
			//	*(pix++) = value;
			//	value = 0;

			// [comment]
			// Generate primary ray direction. Compute the x and y position
			// of the ray in screen space. This gives a point on the image plane
			// at z=1. From there, we simply compute the direction by normalized
			// the resulting vec3f variable. This is similar to taking the vector
			// between the point on the image plane and the camera origin, which
			// in camera space is (0,0,0):
			//
			// ray.dir = normalize(Vec3f(x,y,-1) - Vec3f(0));
			// [/comment]
#ifdef MAYA_STYLE
			float x = (2 * (i + 0.5) / (float)options.width - 1) * scale;
			float y = (1 - 2 * (j + 0.5) / (float)options.height) * scale * 1 / imageAspectRatio;
#else

			float x = (2 * (i + 0.5) / (float)w - 1) * imageAspectRatio * scale;
			float y = (1 - 2 * (j + 0.5) / (float)h) * scale;
#endif
			// [comment]
			// Don't forget to transform the ray direction using the camera-to-world matrix.
			// [/comment]
			Vec3f dir;
			camera.cameraToWorld().multDirMatrix(Vec3f(x, y, -1), dir);
			dir.normalize();
			*(pix++) = castRay(orig, dir, objects);
			//fprintf(stderr, "\r%3d%c", int(j / (float)h * 100), '%');
		}
	}
	ImagePNG* png_image = new ImagePNG(w, h);

	for (int x = 0; x < w; ++x) {
		for (int y = 0; y < h; ++y) {
			int index = 4 * w * y + 4 * x;
			char r = (char)(255 * clamp(0, 1, framebuffer[x + y*w].x));
			char g = (char)(255 * clamp(0, 1, framebuffer[x + y*w].y));
			char b = (char)(255 * clamp(0, 1, framebuffer[x + y*w].z));
			png_image->pixels[index + 0] = r;
			png_image->pixels[index + 1] = g;
			png_image->pixels[index + 2] = b;
			png_image->pixels[index + 3] = 255;
		}
	}
	png_image->saveImage("output.png");

	delete[] framebuffer;
}


Image* RayCasting::RenderScene(/*vector<Sphere> objects, CameraDefinition camera,*/ int w, int h)
{
	Image* image = new Image(w, h);

	const float kInfinity = INFINITY;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	// creating the scene (adding objects and lights)
	std::vector<Object*> objects;

	// generate a scene made of random spheres
	int numSpheres = 0;
	gen.seed(0);
	for (int i = 0; i < numSpheres; ++i) {
		Vec3f randPos((0.5 - dis(gen)) * 10, (0.5 - dis(gen)) * 10, (0.5 + dis(gen) * 10));
		float randRadius = (0.5 + dis(gen) * 0.5);
		objects.push_back(dynamic_cast<Object*>(new Sphere(randPos, randRadius, Vec3f(dis(gen), dis(gen), dis(gen)), 1, 0.5)));

	}
	objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(0.0, -10004, -20), 10000, Vec3f(0.20, 0.20, 0.20), 0, 0)));
	//objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(0.0, 0, -20), 4, Vec3f(1.00, 0.32, 0.36), 1, 0.5)));
	//objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(5.0, -1, -15), 2, Vec3f(0.90, 0.76, 0.46), 1, 0.0)));
	objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(-15.0, 0, -10), 5, Vec3f(0.5, 1, 0), 0, 0.5)));
	objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(10, 0, 10), 3, Vec3f(0, 0.8, 0.8), 0, 0.5)));
	objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(0, 0, 0), 8, Vec3f(0, 0, 1), 1, 1.33)));

	objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(0.0, 20, 10), 5, Vec3f(0, 0, 0), 0, 0.0, Vec3f(3))));
	objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(0.0, 25, -20), 5, Vec3f(0, 0, 0), 0, 0.0, Vec3f(1))));
	int width = w, height = h;
	// setting up options
	/* Options options;
	options.width = 640;
	options.height = 480;
	options.fov = 51.52;
	options.cameraToWorld = */
	//Matrix44f(0.945519, 0, -0.325569, 0, -0.179534, 0.834209, -0.521403, 0, 0.271593, 0.551447, 0.78876, 0, 4.208271, 8.374532, 17.932925, 1);
	double fov = 60;
	Matrix44f m(0.945519, 0, -0.325569, 0, -0.179534, 0.834209, -0.521403, 0, 0.271593, 0.551447, 0.78876, 0, 4.208271, 8.374532, 17.932925, 1);
	//m.multVecMatrix(Vec3f(0, 10, 20), Vec3f(1,1,1));
	Camera myCam(m, fov);
	// finally, render
	render(objects, myCam, width, height, image);

	return image;
}