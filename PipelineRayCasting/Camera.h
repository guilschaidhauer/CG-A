#ifndef _Camera_H
#define _Camera_H

#include "Object.h"

class Camera {
	//Vect campos, camdir, camright, camdown;
	
	public:
	
	Camera ();
	Camera(Matrix44f ctw, double fov);
	//Camera (Vect, Vect, Vect, Vect);
	Matrix44f cameraToWorld(){return camToWorld;}
	double FOV(){return fov;}
	// method functions
//	Vect getCameraPosition () { return campos; }
	//Vect getCameraDirection () { return camdir; }
	//Vect getCameraRight () { return camright; }
	//Vect getCameraDown () { return camdown; }

	Vec3f position;

private:
	Matrix44f camToWorld;
	double fov;
	
};

#endif
