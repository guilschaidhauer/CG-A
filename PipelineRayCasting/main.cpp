#include <iostream>
#include "paramsFile->h"
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
	myParamsFile = myEntryPocessor->processEntry(paramsFile);
	cout << myparamsFile->objects.at(0);
}

void processRender()
{
	cout << myparamsFile->objects.at(0);
	image = myRender->RenderScene(myparamsFile->objects, myparamsFile->cameraDefinition, myparamsFile->width, myparamsFile->height);
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