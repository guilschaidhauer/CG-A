#include "Camera.h"

Camera::Camera() {
	//campos = Vec3f(0, 0, 0);
	//camdir = Vec3f(0, 0, 1);
	//camright = Vec3f(0, 0, 0);
	//camdown = Vec3f(0, 0, 0);
}

Camera::Camera(Matrix44f ctw, double f) {
	camToWorld = ctw;
	fov = f;

}
