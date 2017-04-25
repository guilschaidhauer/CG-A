#include "EdgeFilter.h"



EdgeFilter::EdgeFilter()
{
	matrix[0][0] = 0;
	matrix[0][1] = 1;
	matrix[0][2] = 0;
	matrix[1][0] = 1;
	matrix[1][1] = -4;
	matrix[1][2] = 1;
	matrix[2][0] = 0;
	matrix[2][1] = 1;
	matrix[2][2] = 0;

	factor = 1.0;
	bias = 0.0;
}


EdgeFilter::~EdgeFilter()
{
}
