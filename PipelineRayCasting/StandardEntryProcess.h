#pragma once
#include "EntryProcessor.h"

class StandardEntryProcess : public EntryProcessor
{
public:
	StandardEntryProcess();
	~StandardEntryProcess();

	ParamsFile processEntry(ParamsFile *paramsFile) override;
};

