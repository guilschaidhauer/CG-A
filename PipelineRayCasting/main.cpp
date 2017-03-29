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

Vec3 randomColor()
{
	return Vec3(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
}

Vec3 randomPosition()
{
	return Vec3(rand() % 500 + 1, rand() % 500 + 1, (rand() % 50 + 15) * -1);
}

//TODO use params from file instead
void defineParams()
{
	myParamsFile.output.w = 500;
	myParamsFile.output.h = 500;

	Vec3 blue = Vec3(0, 0, 255);
	Vec3 red = Vec3(255, 0, 0);

	Sphere blueSphere(Vec3(myParamsFile.output.w * 0.5, myParamsFile.output.h *0.5, -15), 50, randomColor());
	Sphere redSphere(Vec3(myParamsFile.output.w * 0.65, myParamsFile.output.h *0.65, -15), 30, randomColor());

	myParamsFile.objects.push_back(blueSphere);
	myParamsFile.objects.push_back(redSphere);

	/*for (int i = 0; i < 10; i++)
	{
	Sphere blueSphere(randomPosition(), 30, randomColor());
	myParamsFile.objects.push_back(blueSphere);
	}*/
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
	myEntryPocessor->processEntry(paramsFile);
}

void processRender(vector<Sphere> objects, CameraDefinition camera, float w, float h)
{
	image = myRender->RenderScene(objects, camera, w, h);
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
	processRender(myParamsFile.objects, myParamsFile.cameraDefinition, myParamsFile.output.w, myParamsFile.output.h);

	//Add filter
	processImage();

	//Create image
	processOutput("RenderedImage.bmp");

	system("pause");
	return 0;
}