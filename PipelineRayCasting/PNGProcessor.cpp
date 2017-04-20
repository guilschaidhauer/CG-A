#include "PNGProcessor.h"



PNGProcessor::PNGProcessor()
{
}


PNGProcessor::~PNGProcessor()
{
}

void PNGProcessor::processImage(Image* image)
{
	currentImage = image;
	grayScale();
	image = currentImage;
}

void PNGProcessor::grayScale() {
	std::vector<unsigned char> grayimage = currentImage->pixels;
	for (int x = 0; x < (int)currentImage->w; x++) {
		for (int y = 0; y < (int)currentImage->h; y++) {
			Color color;
			int index = 4 * currentImage->w * y + 4 * x;
			color.setColorRed((int)grayimage[index + 0]);
			color.setColorGreen((int)grayimage[index + 1]);
			color.setColorBlue((int)grayimage[index + 2]);
			//float test = sqrt((color.r + color.g + color.b) / 3);
			//color.r *= 0.30f;
			//color.g *= 0.59f;
			//color.b *= 0.11f;
			float average = ((color.getColorRed() + color.getColorGreen() + color.getColorBlue()) / 3);
			grayimage[index + 0] = average;//color.r;
			grayimage[index + 1] = average;//color.g;
			grayimage[index + 2] = average;//color.b;
			grayimage[index + 3] = 255;
		}
	}
	currentImage->pixels = grayimage;
//	currentimage = grayimage;
}
