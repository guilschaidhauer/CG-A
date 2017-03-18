#pragma once
class ImageProcessor
{
public:
	ImageProcessor();
	~ImageProcessor();

	virtual void processImage(void) = 0;
};

