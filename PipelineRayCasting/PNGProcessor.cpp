#include "PNGProcessor.h"



PNGProcessor::PNGProcessor()
{
	originalImage = NULL;
}


PNGProcessor::~PNGProcessor()
{
}

void PNGProcessor::processImage(int type,Image* image)
{
	if (originalImage == NULL) {
		originalPixels.resize(image->w * image->h * 4);
		//memcpy(&originalPixels,&image->pixels, image->pixels.size() );
		//copy_n(originalPixels, image->pixels, sizeof(image->pixels));
		 // = image->pixels;
		//originalImage->pixels = 
			//memcpy(&originalImage->pixels, &image->pixels,sizeof(unsigned char)image->pixels));
	}

	//_sharpen.applyFilter(image);


	switch (type)
	{
	case PNGProcessor::SHARPEN:
		_sharpen.doIt(image);
		break;
	case PNGProcessor::ORIGINAL:
		getOriginal(image);
		break;
	case PNGProcessor::BLUR:
		_blur.doIt(image);
		break;
	case PNGProcessor::EDGE:
		_edge.doIt(image);
		break;
	case PNGProcessor::GRAY:
		grayScale(image);
		break;
	default:
		break;
	}

}

void PNGProcessor::getOriginal(Image* image) {
	image->pixels = originalPixels;

}

void PNGProcessor::setOriginal(Image* image) {
	//originalImage->pixels = image->pixels;
	//for (int x = 0; x < (int)image->w; x++) {
	//	for (int y = 0; y < (int)image->h; y++) {
	//		int index = 4 * image->w * y + 4 * x;
	//		originalImage->pixels[index] = image->pixels[index];
	//		//originalImage->pixels[index + 1] = image->pixels[index + 1];
	//		//originalImage->pixels[index + 2] = image->pixels[index + 2];
	//		//originalImage->pixels[index + 3] = image->pixels[index + 3];
	//	}
	//}
}

void PNGProcessor::grayScale(Image* image) {
	std::vector<unsigned char> grayimage = image->pixels;
	for (int x = 0; x < (int)image->w; x++) {
		for (int y = 0; y < (int)image->h; y++) {
			Color color;
			int index = 4 * image->w * y + 4 * x;
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
	image->pixels = grayimage;
}
