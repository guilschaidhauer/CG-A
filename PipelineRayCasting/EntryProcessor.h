#pragma once
#include "ParamsFile.h"
#include <fstream>

using namespace std;

class EntryProcessor
{
public:
	EntryProcessor();
	~EntryProcessor();

	virtual ParamsFile processEntry(ParamsFile *paramsFile) = 0;

	virtual ParamsFile processEntry2(ParamsFile *paramsFile) = 0;
};

		