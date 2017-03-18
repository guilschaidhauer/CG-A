#include "RayCasting.h"



RayCasting::RayCasting()
{
}


RayCasting::~RayCasting()
{
}


/*
A(xA,yA,zA) and B(xB,yB,zB) be two different points on the line
C(xC,yC,zC) be the center of the sphere
r be the radius of the sphere
the cartesian equation of the sphere is:

(x-xC)²+(y-yC)²+(z-zC)²=r²
let us write the parametric equation of the line (parameter d):

x = xA + d*(xB-xA)
y = yA + d*(yB-yA)
z = zA + d*(zB-zA)
replacing in the sphere equation yields:

(xA + d(xB-xA) - xC)²+(yA + d(yB-yA) - yC)²+(zA + d(zB-zA) - zC)²=r²
This is a quadratic equation in d, where the discrimant is:

Delta=b²-4*a*c
with:

a = (xB-xA)²+(yB-yA)²+(zB-zA)²
b = 2*((xB-xA)(xA-xC)+(yB-yA)(yA-yC)+(zB-zA)(zA-zC))
c = (xA-xC)²+(yA-yC)²+(zA-zC)²-r²


A = camera
B = rayEndPoint
C = objectPosition

*/

void RayCasting::RenderScene(vector<Sphere> objects, CameraDefinition camera, float w, float h)
{
	float raySize = 15;

	/*Sphere sphere = objects[0];

	for (int i = 0; i < h; i++) 
	{
		for (int j = 0; j < w; j++)
		{
			Position directionVector;
			directionVector.x = j - camera.ex;
			directionVector.y = i - camera.ey;
			directionVector.z = 0;

			Position rayEndPoint;
			rayEndPoint.x = camera.ex + (raySize * directionVector.x);
			rayEndPoint.y = camera.ey + (raySize * directionVector.y);
			rayEndPoint.z = camera.ez + (raySize * directionVector.z);

			float a = pow(rayEndPoint.x - camera.ex, 2) + pow(rayEndPoint.y - camera.ey, 2) + pow(rayEndPoint.z - camera.ez, 2);
			float b = 2 * ((rayEndPoint.x - camera.ex)*(rayEndPoint.x - sphere.rx) + (rayEndPoint.y - camera.ey)*(camera.ey - sphere.ry) + (rayEndPoint.z - camera.ez) * (camera.ez - sphere.rz));
			float c = pow(camera.ex - sphere.rx, 2) + pow(camera.ey - sphere.ry, 2) + pow(camera.ez - sphere.rz, 2) - pow(sphere.radius, 2);

			float delta = pow(b, 2) - 4 * a * c;

			if (delta < 0)
			{
				cout << "no interaction" << endl;
			}
			else
			{
				cout << "THERE IS INTERACTION" << endl;
			}
		}
	}*/
}

