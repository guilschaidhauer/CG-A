#include "BlurFilter.h"



BlurFilter::BlurFilter()
{
	float blurIndex = 0.2f;
	matrix[0][0] = 0;
	matrix[0][1] = blurIndex;
	matrix[0][2] = 0;
	matrix[1][0] = blurIndex;
	matrix[1][1] = blurIndex;
	matrix[1][2] = blurIndex;
	matrix[2][0] = 0;
	matrix[2][1] = blurIndex;
	matrix[2][2] = 0;

	factor = 1.0;
	bias = 0.0;
}


BlurFilter::~BlurFilter()
{
}
