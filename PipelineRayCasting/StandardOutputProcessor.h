#pragma once
#include "OutputProcessor.h"

class StandardOutputProcessor : public OutputProcessor
{
public:
	StandardOutputProcessor();
	~StandardOutputProcessor();

	void processOutput(string fileName, int w, int h, int dpi, RGBType *data) override;
};

