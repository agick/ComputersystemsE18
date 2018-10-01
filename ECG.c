#include "sensor.h"
#include "filters.h"
#include "qsr.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Main function for organizing the program execution.
// The functions and object predefined are just for inspiration.
// Please change orden,names arguments to fit your solution.

int main(void)
{

    //INITIALIZE FILTER STRUCTURE
    FILTERS_params filters_params;
    filters_params = initFilterParams(&filters_params);

    //INITIALIZE QSR STRUCTURE
    QSR_params qsr_params;
    qsr_params = initQSRParams(&qsr_params);

    //OPEN FILE
	FILE *file;                  // Pointer to a file object
	file = openfile("ECG.txt");



	int i = 1;
	int k;
	unsigned long Num = 0;
	int run = 1;
	//RUN PROGRAM
	displayNames();
	while(run <= 10000) {
		Num++;
		run++;
		//GET INPUT AND WRITE TO ARRAY X
		i = getNextData(file);
		for(k = (sizeof(filters_params.X) / sizeof(int))-1; k > 0; k--){
			filters_params.X[k] = filters_params.X[k-1];
		}
		filters_params.X[0] = i;

		//GO THROUGH ALL FILTERS
		lowPassFilter(&filters_params);
		highPassFilter(&filters_params);
		derivative(&filters_params);
		squaring(&filters_params);
		mwi(&filters_params);

		//WRITE Y VALUE TO XP ARRAY GOING INTO PEAK DETECTION
		for(k = (sizeof(qsr_params.Xp) / sizeof(int))-1; k > 0; k--){
			qsr_params.Xp[k] = qsr_params.Xp[k-1];
		}
		qsr_params.Xp[0] = filters_params.Y;

		//RUN PEAK DETECTION
		peakDetection(&qsr_params);

		//PRINT VALUES
		displayData(&qsr_params);
	}
	return 0;
}

