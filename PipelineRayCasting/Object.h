#ifndef _OBJECT_H
#define _OBJECT_H

//#include "Ray.h"
#include "geometry.h"
#include "Color.h"

//class Object
//{
// public:
//    Object() : color(dis(gen), dis(gen), dis(gen)) {}
//    virtual ~Object() {}
//    // Method to compute the intersection of the object with a ray
//    // Returns true if an intersection was found, false otherwise
//    // See method implementation in children class for details
//    virtual bool intersect(const Vec3f &, const Vec3f &, float &) const = 0;
//    // Method to compute the surface data such as normal and texture coordnates at the intersection point.
//    // See method implementation in children class for details
//    virtual void getSurfaceData(const Vec3f &, Vec3f &, Vec2f &) const = 0;
//    Vec3f color;
//};


class Object {	
	public:
	Vec3f surfaceColor, emissionColor;      /// surface color and emission (light)
	float transparency, reflection, refraction;         /// surface transparency and reflectivity
	Object ();
	virtual ~Object() {}
	// method functions
	virtual Color getColor () { return Color (0.0, 0.0, 0.0, 0); }
	
	//virtual Vec3f getNormalAt(Vec3f intersection_position) {
	//	return Vec3f (0, 0, 0);
	//}

	// Method to compute the intersection of the object with a ray
    // Returns true if an intersection was found, false otherwise
    // See method implementation in children class for details
    virtual bool intersect(const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1) const = 0;
    // Method to compute the surface data such as normal and texture coordnates at the intersection point.
    // See method implementation in children class for details
    virtual void getSurfaceData(const Vec3f &, Vec3f &, Vec2f &) const = 0;
	
	//virtual double findIntersection(Ray ray) {
	//	return 0;
	//}
	
};

#endif
