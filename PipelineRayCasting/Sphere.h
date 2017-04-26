#ifndef _SPHERE_H
#define _SPHERE_H

#include "math.h"
#include "Object.h"
//#include "geometry.h"
//#include "Color.h"


class Sphere : public Object {
	public:
	  
   
	Sphere ();
	//Sphere(const Vec3f &c, const double &r, const Color);// : radius(r), radius2(r *r ), center(c) {}
	 Sphere(
        const Vec3f &c,
        const float &r,
        const Vec3f &sc,
        const float &refl = 0,
        const float &transp = 0,
        const Vec3f &ec = 0);
	//Sphere (Vect, double, Color);
	virtual void getSurfaceData(const Vec3f &Phit, Vec3f &Nhit, Vec2f &tex) const ;
	// method functions
	Vec3f getSphereCenter () { return center; }
	double getSphereRadius () { return radius; }
	virtual Color getColor () { return color; }
	void setCenter(Vec3f c) { center = c; }
	void setColor(Vec3f c) { color.setColorRed(c.x);  color.setColorGreen(c.y); color.setColorBlue(c.z); }
	virtual bool intersect(const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1) const ; 

	//virtual Vect getNormalAt(Vect point) {
	//	// normal always points away from the center of a sphere
	//	Vect normal_Vect = point.vectAdd(center.negative()).normalize();
	//	return normal_Vect;
	//}
	
	//virtual double findIntersection(Ray ray) {
	//	Vect ray_origin = ray.getRayOrigin();
	//	double ray_origin_x = ray_origin.getVectX();
	//	double ray_origin_y = ray_origin.getVectY();
	//	double ray_origin_z = ray_origin.getVectZ();
	//	
	//	Vect ray_direction = ray.getRayDirection();
	//	double ray_direction_x = ray_direction.getVectX();
	//	double ray_direction_y = ray_direction.getVectY();
	//	double ray_direction_z = ray_direction.getVectZ();
	//	
	//	Vect sphere_center = center;
	//	double sphere_center_x = sphere_center.getVectX();
	//	double sphere_center_y = sphere_center.getVectY();
	//	double sphere_center_z = sphere_center.getVectZ();
	//	
	//	double a = 1; // normalized
	//	double b = (2*(ray_origin_x - sphere_center_x)*ray_direction_x) + (2*(ray_origin_y - sphere_center_y)*ray_direction_y) + (2*(ray_origin_z - sphere_center_z)*ray_direction_z);
	//	double c = pow(ray_origin_x - sphere_center_x, 2) + pow(ray_origin_y - sphere_center_y, 2) + pow(ray_origin_z - sphere_center_z, 2) - (radius*radius);
	//	
	//	double discriminant = b*b - 4*c;
	//	
	//	if (discriminant > 0) {
	//		/// the ray intersects the sphere
	//		
	//		// the first root
	//		double root_1 = ((-1*b - sqrt(discriminant))/2) - 0.000001;
	//		
	//		if (root_1 > 0) {
	//			// the first root is the smallest positive root
	//			return root_1;
	//		}
	//		else {
	//			// the second root is the smallest positive root
	//			double root_2 = ((sqrt(discriminant) - b)/2) - 0.000001;
	//			return root_2;
	//		}
	//	}
	//	else {
	//		// the ray missed the sphere
	//		return -1;
	//	}
	//}

private:

		Vec3f center;
		double radius, radius2;
		Color color;
	
};

#endif
