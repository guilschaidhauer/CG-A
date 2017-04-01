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

//TODO use params from file instead
void defineParams()
{

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

void processRender(/*vector<Sphere> objects, CameraDefinition camera,*/ float w, float h)
{
	//image = myRender->RenderScene(objects, camera, w, h);
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
	//processRender(myParamsFile.objects, myParamsFile.cameraDefinition, myParamsFile.output.w, myParamsFile.output.h);

	//Add filter
	processImage();

	//Create image
	processOutput("RenderedImage.bmp");

	system("pause");
	return 0;
}