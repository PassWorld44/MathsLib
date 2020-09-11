#include "MyMaths.h"

double pow(double nbr, int exp)
{
	double result = nbr;
	for(int i = 0; i < exp - 1; ++i) 
	// minus one cause we already have 
	// one time the nbr in the result
	{
		result *= nbr;
	}

	if(exp == 0)
		return 1;
	else
		return result;
}