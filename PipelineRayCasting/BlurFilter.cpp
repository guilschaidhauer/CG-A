#include "BlurFilter.h"



BlurFilter::BlurFilter()
{
	matrix[0][0] = 0;
	matrix[0][1] = 0.2;
	matrix[0][2] = 0;
	matrix[1][0] = 0.2;
	matrix[1][1] = 0.2;
	matrix[1][2] = 0.2;
	matrix[2][0] = 0;
	matrix[2][1] = 0.2;
	matrix[2][2] = 0;

	matrix[0][0] = 1;
	matrix[0][1] = 1;
	matrix[0][2] = 1;
	matrix[1][0] = 1;
	matrix[1][1] = 1;
	matrix[1][2] = 1;
	matrix[2][0] = 1;
	matrix[2][1] = 1;
	matrix[2][2] = 1;


	factor = 1.0;
	bias = 0.0;
}


BlurFilter::~BlurFilter()
{
}
