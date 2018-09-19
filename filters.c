#include "filters.h"
// Feel free to change return statement and arguments

void lowPassFilter(FILTERS_params *params)
{
	updateLpfParams(params);
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
	updateHpfParams(params);
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
	updateSqrParams(params);
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

FILTERS_params updateLpfParams(FILTERS_params *params)
{
	int i;
	for(i = (sizeof(params->lpfX) / sizeof(int))-1; i > 0; i--){
		params->lpfX[i] = params->lpfX[i-1];
	}
	return *params;
}

FILTERS_params updateHpfParams(FILTERS_params *params)
{
	int i;
	for(i = (sizeof(params->hpfX) / sizeof(int))-1; i > 0; i--){
		params->hpfX[i] = params->hpfX[i-1];
	}
	return *params;
}

FILTERS_params updateSqrParams(FILTERS_params *params)
{
	int i;
	for(i = (sizeof(params->sqrX) / sizeof(int))-1; i > 0; i--){
		params->sqrX[i] = params->sqrX[i-1];
	}
	return *params;
}

FILTERS_params updateFilterParams(FILTERS_params *params)
{
	int i;
	for(i = (sizeof(params->Y) / sizeof(int))-1; i > 0; i--){
		params->Y[i] = params->Y[i-1];
	}
	for(i = (sizeof(params->X) / sizeof(int))-1; i > 0; i--){
		params->X[i] = params->X[i-1];
	}
	return *params;
}

FILTERS_params initFilterParams(FILTERS_params *params)
{
	int i;
	for(i = 0; i < sizeof(params->Y) / sizeof(int); i++){
		params->Y[i] = 0;
	}
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

	return *params;
	//Kommentar
}
