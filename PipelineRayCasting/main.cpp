#include <iostream>
#include "ParamsFile.h"
#include "RayCasting.h"
#include "PNGProcessor.h"
#include "StandardOutputProcessor.h"
#include "StandardEntryProcess.h"
#include "Image.h"

using namespace std;

ParamsFile myParamsFile;
Image *image;
Render *myRender;
ImageProcessor *myImageProcessor;
OutputProcessor *myOutputProcessor;
EntryProcessor *myEntryPocessor;

//TODO use params from file instead
void defineParams()
{
	myParamsFile.output.w = 500;
	myParamsFile.output.h = 500;

	Vec3 blue = Vec3(0, 0, 255);
	Vec3 red = Vec3(255, 0, 0);

	Sphere blueSphere(Vec3(myParamsFile.output.w * 0.5, myParamsFile.output.h *0.5, -10), 25, blue);
	Sphere redSphere(Vec3(myParamsFile.output.w * 0.25, myParamsFile.output.h *0.25, -10), 50, red);

	myParamsFile.objects.push_back(blueSphere);
	myParamsFile.objects.push_back(redSphere);
}

void init()
{
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