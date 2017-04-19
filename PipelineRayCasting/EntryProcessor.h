#pragma once
#include "paramsFile->h"
#include <fstream>

using namespace std;

class EntryProcessor
{
public:
	EntryProcessor();
	~EntryProcessor();

	virtual ParamsFile processEntry(ParamsFile *paramsFile) = 0;
};

