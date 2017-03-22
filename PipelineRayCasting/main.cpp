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
	myParamsFile.output.w = 1024;
	myParamsFile.output.h = 768;
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
	//Image *image = new Image(w, h);

	image->dpi = 72;
	int n = image->w * image->h;


	//Comment this and implement Raycasting on the render
	image->pixels = new RGBType[n];

	int pixelAtual;
	for (int x = 0; x < image->w; x++)
	{
		for (int y = 0; y < image->h; y++)
		{
			pixelAtual = y*image->w + x;

			image->pixels[pixelAtual].r = 255;
			image->pixels[pixelAtual].g = 0;
			image->pixels[pixelAtual].b = 0;
		}
	}

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