#include <iostream>
#include "ParamsFile.h"
#include "RayCasting.h"
#include "PNGProcessor.h"
#include "StandardOutputProcessor.h"
#include "StandardEntryProcess.h"
#include "Image.h"
#include <time.h>   

using namespace std;

ParamsFile myParamsFile;
Image *image;
Render *myRender;
ImageProcessor *myImageProcessor;
OutputProcessor *myOutputProcessor;
EntryProcessor *myEntryPocessor;

Matrix44f lookAt(Vec3f pos, Vec3f target, Vec3f up)
{
	Vec3f z = (target - pos).normalize();
	Vec3f x = up.crossProduct(z).normalize();
	Vec3f y = z.crossProduct(x).normalize();

	Matrix44f mat;

	mat[0][0] = x.x;
	mat[0][1] = x.y;
	mat[0][2] = x.z;

	mat[1][0] = y.x;
	mat[1][1] = y.y;
	mat[1][2] = y.z;

	mat[2][0] = z.x;
	mat[2][1] = z.y;
	mat[2][2] = z.z;

	mat[3][0] = pos.x;
	mat[3][1] = pos.y;
	mat[3][2] = pos.z;

	mat[3][3] = 1;

	return mat;
}

void defineParams()
{
	myParamsFile.objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(0.0, 0.0, 0.0), 0.8, Vec3f(0.0, 0.8, 0.0), 0, 0.5)));
	//myParamsFile.objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(-2, 0.0, 0.0), 0.8, Vec3f(0.8, 0.0, 0.0), 0, 0.5)));
	//myParamsFile.objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(2, 0.0, 0.0), 0.8, Vec3f(0.0, 0.0, 0.8), 0, 0.5)));

	myParamsFile.objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(0.0, 20, 10), 5, Vec3f(0, 0, 0), 0, 0.0, Vec3f(3))));
	//myParamsFile.objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(0.0, 25, -20), 5, Vec3f(0, 0, 0), 0, 0.0, Vec3f(1))));

	//ParamsFile otherParams;
	//myEntryPocessor->processEntry(&otherParams);

	//myParamsFile.objects = otherParams.objects;

	//myParamsFile.objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(-15.0, 0, -10), 5, Vec3f(0.5, 0.5, 0), 1, 1.33)));


	//myParamsFile.objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(0.0, 20, 10), 5, Vec3f(0, 0, 0), 0, 0.0, Vec3f(3))));
	//myParamsFile.objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(0.0, 25, -20), 5, Vec3f(0, 0, 0), 0, 0.0, Vec3f(1))));


	double fov = 60;
	Matrix44f m(0.945519, 0, -0.325569, 0, -0.179534, 0.834209, -0.521403, 0, 0.271593, 0.551447, 0.78876, 0, 4.208271, 8.374532, 17.932925, 1);

	Vec3f pos(0, 0, -1);
	Vec3f target(0, 0, 0);
	//target = target - pos;
	//target = target.normalize();

	Camera myCam(lookAt(pos, /*pos + */target, Vec3f(0, -1, 0)), fov);

	myParamsFile.cameraDefinition = myCam;

	myParamsFile.width = 640;
	myParamsFile.height = 480;
}

void init()
{
	srand(time(NULL));

	myRender = new RayCasting();
	myImageProcessor = new PNGProcessor();
	myOutputProcessor = new StandardOutputProcessor();
	myEntryPocessor = new StandardEntryProcess();

	defineParams();
}

void processEntry(ParamsFile paramsFile) 
{
	ParamsFile newParams;
	myEntryPocessor->processEntry2(&newParams);
	myParamsFile.objects = newParams.objects;

	Camera myCam(lookAt(newParams.cameraDefinition.position, newParams.cameraDefinition.getTarget(), Vec3f(0, -1, 0)), newParams.cameraDefinition.FOV());

	//Camera myCam(lookAt(pos, /*pos + */target, Vec3f(0, -1, 0)), fov);
	myParamsFile.cameraDefinition = myCam;
	myParamsFile.width = newParams.width;
	myParamsFile.height = newParams.height;

	//cout << myparamsFile.objects.at(0);
}

void processRender()
{
	//cout << myparamsFile->objects.at(0);
	image = myRender->RenderScene(myParamsFile.objects, myParamsFile.cameraDefinition, myParamsFile.width, myParamsFile.height);
}

void processImage()
{
	myImageProcessor->processImage();
}

void processOutput(string fileName)
{
	image->saveImage(fileName);
}

int main(int argc, char** argv)
{
	init();

	//Read file
	processEntry(myParamsFile);

	//Add configs from file to myParamsFile

	//Render Scene
	processRender();

	//Add filter
	processImage();

	//Create image
	processOutput("OutImage.bmp");

	system("pause");
	return 0;
}