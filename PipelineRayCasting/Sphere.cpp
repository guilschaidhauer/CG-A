#include "Sphere.h"

Sphere::Sphere() {
	center = Vec3f(0, 0, 0);
	radius = 1.0;
	color = Color(0.5, 0.5, 0.5, 0);
	radius2 = 1;
}

Sphere::Sphere(
        const Vec3f &c,
        const float &r,
        const Vec3f &sc,
        const float &refl,
		const float &refr,
        const float &transp,
        const Vec3f &ec) 
{
        center = (c); 
		radius = (r); 
		radius2 = (r * r); 
		surfaceColor = (sc); 
		emissionColor = (ec);
		transparency = (transp); 
		reflection = (refl);
		refraction = (refr);
}

/*Sphere::Sphere(const Vec3f &c, const double &r, const Color colorValue) {
	center = c;
	radius = r;
	color = colorValue;
	radius2 = r*r;
}*/

void Sphere::getSurfaceData(const Vec3f &Phit, Vec3f &Nhit, Vec2f &tex) const{
		//PHIT - hit point
		//NHIT - normal
        Nhit = Phit - center;
        Nhit.normalize();
        // In this particular case, the normal is simular to a point on a unit sphere
        // centred around the origin. We can thus use the normal coordinates to compute
        // the spherical coordinates of Phit.
        // atan2 returns a value in the range [-pi, pi] and we need to remap it to range [0, 1]
        // acosf returns a value in the range [0, pi] and we also need to remap it to the range [0, 1]
        tex.x = (1 + atan2(Nhit.z, Nhit.x) / M_PI) * 0.5;
        tex.y = acosf(Nhit.y) / M_PI;
}

bool Sphere::intersect(const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1) const
    {
        //float t0, t1; // solutions for t if the ray intersects
//#if 0
        // geometric solution
        Vec3f L = center - rayorig;
        float tca = L.dotProduct(raydir);
        if (tca < 0) return false;
        float d2 = L.dotProduct(L) - tca * tca;
        if (d2 > radius2) return false;
        float thc = sqrt(radius2 - d2);
        t0 = tca - thc;
        t1 = tca + thc;
       
     //   return true;
//#else
//        // analytic solution
//        Vec3f L = rayorig - center;
//        float a = raydir.dotProduct(raydir);
//        float b = 2 * raydir.dotProduct(L);
//        float c = L.dotProduct(L) - radius2;
//        if (!solveQuadratic(a, b, c, t0, t1)) return false;
//#endif
//        if (t0 > t1) std::swap(t0, t1);
//
//        if (t0 < 0) {
//            t0 = t1; // if t0 is negative, let's use t1 instead
//            if (t0 < 0) return false; // both t0 and t1 are negative
//        }
//
//        t = t0;
//
        return true;
}