#include "Filter.h"

Filter::Filter() {

}

Filter::~Filter() {

}


void Filter::doIt(Image* image) {
	std::vector<unsigned char> convolution;
	std::vector<unsigned char> img_pixels;
	convolution = image->pixels;
	img_pixels = image->pixels;
	for (int x = 0; x < image->w; x++)
		for (int y = 0; y < image->h; y++)
		{
			int index = 4 * image->w * y + 4 * x;
			double red = 0.0, green = 0.0, blue = 0.0;
			Color color;
			//multiply every value of the filter with corresponding image pixel
			for (int filterY = 0; filterY < filterHeight; filterY++)
				for (int filterX = 0; filterX < filterWidth; filterX++)
				{
					int imageX = (x - filterWidth / 2 + filterX + image->w) % image->w;
					int imageY = (y - filterHeight / 2 + filterY + image->h) % image->h;
					int index2 = 4 * image->w * imageY + 4 * imageX;
					red += (int)img_pixels[index2 + 0] * matrix[filterY][filterX];
					green += (int)img_pixels[index2 + 1] * matrix[filterY][filterX];
					blue += (int)img_pixels[index2 + 2] * matrix[filterY][filterX];
				}

			//truncate values smaller than zero and larger than 255
			convolution[index + 0] = min(max(int(factor * red + bias), 0), 255);
			convolution[index + 1] = min(max(int(factor * green + bias), 0), 255);
			convolution[index + 2] = min(max(int(factor * blue + bias), 0), 255);
			convolution[index + 3] = 255;
			//result[y * w + x].r = min(max(int(factor * red + bias), 0), 255);
			//result[y * w + x].g = min(max(int(factor * green + bias), 0), 255);
			//result[y * w + x].b = min(max(int(factor * blue + bias), 0), 255);
	}
	image->pixels = convolution;
}