#pragma once
#include "ParamsFile.h"

using namespace std;

class EntryProcessor
{
public:
	EntryProcessor();
	~EntryProcessor();

	virtual void processEntry(ParamsFile paramsFile) = 0;
};

