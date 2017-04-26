#pragma once
#include "EntryProcessor.h"
#include <sstream>

class StandardEntryProcess : public EntryProcessor
{
public:
	StandardEntryProcess();
	~StandardEntryProcess();

	ParamsFile processEntry(ParamsFile *paramsFile) override;

	ParamsFile processEntry2(ParamsFile *paramsFile) override;
	
	string readRestOfLine(stringstream& line);
	
		bool strContains(stringstream& line, string part);
};

