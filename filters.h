#ifndef FILTERS_H
#define FILTERS_H

// Feel free to change return statement and arguments

typedef struct FILTERS_params
{ // Structure for QRS parameters
	int Y[2];
	int X[13];
	int lpfX[33];
	int hpfX[6];
	int derX;
	int sqrX[100];
	int FREQ;
	int N;
} FILTERS_params;

FILTERS_params updateFilterParams(FILTERS_params *params);
FILTERS_params initFilterParams(FILTERS_params *params);

FILTERS_params updateLpfParams(FILTERS_params *params);
FILTERS_params updateHpfParams(FILTERS_params *params);
FILTERS_params updateSqrParams(FILTERS_params *params);

void lowPassFilter(FILTERS_params *params);
void highPassFilter(FILTERS_params *params);
void derivative(FILTERS_params *params);
void squaring(FILTERS_params *params);
void mwi(FILTERS_params *params);




// Implement additional filters
 
#endif // FILTERS_H
