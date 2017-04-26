#pragma once
#include "ImageProcessor.h"
#include "SharpenFilter.h"
#include "BlurFilter.h"
#include "EdgeFilter.h"
#pragma warning(disable:4996)
class PNGProcessor : public ImageProcessor
{
public:
	PNGProcessor();
	~PNGProcessor();
	enum processType { SHARPEN, ORIGINAL, BLUR, EDGE, GRAY };
	void grayScale(Image* image);
	void processImage(int type, Image*);
	void getOriginal(Image* image);
	void setOriginal(Image* image);
private:
	Image* originalImage;
	SharpenFilter _sharpen;
	BlurFilter _blur;
	EdgeFilter _edge;
	std::vector<unsigned char> originalPixels;
};

