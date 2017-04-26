#ifndef _Camera_H
#define _Camera_H

#include "Object.h"

class Camera {	
	public:
	
	Camera ();
	Camera(Matrix44f ctw, double fov);
	Matrix44f cameraToWorld(){return camToWorld;}
	double FOV(){return fov;}
	void setFOV(double newFOV) { fov = newFOV; }
	void setTarget(Vec3f newTarget) { target = newTarget; }
	Vec3f getTarget() { return target; }

	Vec3f position;

private:
	Matrix44f camToWorld;
	double fov;
	Vec3f target;
};

#endif
