#include "filters.h"
#include "array.h"
// Feel free to change return statement and arguments

void lowPassFilter(FILTERS_params *params)
{
	//updateLpfParams(params);
	params->lpfX = rightShiftArray(params->lpfX);
	params->lpfX[0] = (int)(
		(2*params->lpfX[1])
		-params->lpfX[2]
		+((params->X[0]
		-(2*params->X[6])
		+params->X[12])
		/params->FREQ)
		);
}

void highPassFilter(FILTERS_params *params)
{
	params->hpfX = rightShiftArray(params->hpfX);
	params->hpfX[0] = (int)(
		params->hpfX[1]
		-(params->lpfX[0]/params->FREQ)
		+params->lpfX[16]
		-params->lpfX[17]
		+(params->lpfX[32]/params->FREQ)
		);

}

void derivative(FILTERS_params *params)
{

	params->derX = (int)(
		((2*params->hpfX[0])
		+params->hpfX[1]
		-params->hpfX[3]
		-(2*params->hpfX[4]))
		/8
		);
}

void squaring(FILTERS_params *params)
{
	params->sqrX = rightShiftArray(params->sqrX);
	params->sqrX[0] = (int)(
			params->derX*params->derX
		);
}

void mwi(FILTERS_params *params)
{
	int i;
	int Nsum = 0;
	for(i = 0; i < params->N; i++)
		Nsum += params->sqrX[i];

	params->Y[0] = (int)(
			Nsum/params->N
		);

}








FILTERS_params initFilterParams(FILTERS_params *params)
{
	int i;
	for(i = 0; i < sizeof(params->X) / sizeof(int); i++){
		params->X[i] = 0;
	}
	for(i = 0; i < sizeof(params->lpfX) / sizeof(int); i++){
		params->lpfX[i] = 0;
	}
	for(i = 0; i < sizeof(params->hpfX) / sizeof(int); i++){
		params->hpfX[i] = 0;
	}
	for(i = 0; i < sizeof(params->sqrX) / sizeof(int); i++){
			params->sqrX[i] = 0;
		}
	params->FREQ = 32;
	params->N = 30;
	params->derX = 0;
	params->Y = 0;

	return *params;
	//Kommentar
}
