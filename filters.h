#ifndef FILTERS_H
#define FILTERS_H

// Feel free to change return statement and arguments

typedef struct FILTERS_params
{ // Structure for QRS parameters
	int Y;		// Output array - data has gone through all filters
	int X[13]; 		// Input array
	int lpfX[33];	// Output array from low pass filter
	int hpfX[5];	// Output array from high pass filter
	int derX;		// Output array from derivative filter
	int sqrX[31];	// Output array from square filter
	int FREQ;		// Common constant for all filters
	int N;			// Window size for Moving window integration
} FILTERS_params;

FILTERS_params initFilterParams(FILTERS_params *params);

void lowPassFilter(FILTERS_params *params);
void highPassFilter(FILTERS_params *params);
void derivative(FILTERS_params *params);
void squaring(FILTERS_params *params);
void mwi(FILTERS_params *params);




// Implement additional filters
 
#endif // FILTERS_H
