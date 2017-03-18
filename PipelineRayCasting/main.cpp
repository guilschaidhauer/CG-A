#include <iostream>
#include "ParamsFile.h"
#include "RayCasting.h"
#include "PNGProcessor.h"
#include "StandardOutputProcessor.h"
#include "StandardEntryProcess.h"
#include "Image.h"

using namespace std;

ParamsFile myParamsFile;
Render *myRender;
ImageProcessor *myImageProcessor;
OutputProcessor *myOutputProcessor;
EntryProcessor *myEntryPocessor;

void init()
{
	myRender = new RayCasting();
	myImageProcessor = new PNGProcessor();
	myOutputProcessor = new StandardOutputProcessor();
	myEntryPocessor = new StandardEntryProcess();
}

void processEntry(ParamsFile paramsFile) 
{
	myEntryPocessor->processEntry(paramsFile);
}

void processRender(vector<Sphere> objects, CameraDefinition camera, float w, float h)
{
	myRender->RenderScene(objects, camera, w, h);
}

void processImage()
{
	myImageProcessor->processImage();
}

void processOutput(string fileName)
{
	//myOutputProcessor->processOutput(fileName);
	Image image;

	image.dpi = 72;
	image.w = 640;
	image.h = 480;
	int n = image.w*image.h;

	RGBType *pixels = new RGBType[n];

	int pixelAtual;
	for (int x = 0; x < image.w; x++)
	{
		for (int y = 0; y < image.h; y++)
		{
			pixelAtual = y*image.w + x;

			pixels[pixelAtual].r = 23;
			pixels[pixelAtual].g = 222;
			pixels[pixelAtual].b = 222;
		}
	}

	image.SaveImage(fileName, image.w, image.h, image.dpi, pixels);
}

int main(int argc, char** argv)
{
	init();

	processEntry(myParamsFile);
	processRender(myParamsFile.objects, myParamsFile.cameraDefinition, myParamsFile.output.w, myParamsFile.output.h);
	processImage();
	processOutput("Test2.bmp");

	system("pause");
	return 0;
}