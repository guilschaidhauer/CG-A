#pragma once
#include "EntryProcessor.h"

class StandardEntryProcess : public EntryProcessor
{
public:
	StandardEntryProcess();
	~StandardEntryProcess();

	void processEntry(ParamsFile paramsFile) override;	
};

