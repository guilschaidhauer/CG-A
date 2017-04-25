#pragma once
#include "Image.h"
#include "Color.h"
class ImageProcessor
{
public:
	ImageProcessor();
	~ImageProcessor();

	//virtual void processImage(Image* image) = 0;

protected:
	Image* currentImage;
};

