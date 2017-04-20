#pragma once
#include "ImageProcessor.h"


class PNGProcessor : public ImageProcessor
{
public:
	PNGProcessor();
	~PNGProcessor();
	void grayScale();
	void processImage(Image*) override;
};

