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
	FILE *file;                  				// Pointer to a file object
	file = openfile("/Users/bruger/Documents/DTU/3.1 Computer Systems/Github/ComputersystemsE18/ECG.txt");

	int i = 1;
	int k;
	unsigned long Num = 0;
	char run = 1;
	//RUN PROGRAM

	while(run) {
		Num++;
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
		for(k = (sizeof(qsr_params.Xp) / sizeof(int))-1; k > 0; k--){		// RIGHT SHIFT XP ARRAY
			qsr_params.Xp[k] = qsr_params.Xp[k-1];							// RIGHT SHIFT
		}																	// RIGHT SHIFT
		qsr_params.Xp[0] = filters_params.Y;								// PUT FILTER OUTPUT Y INTO QSR XP ARRAY

		//RUN PEAK DETECTION
		peakDetection(&qsr_params);

		//PRINT VALUES
		displayData(&qsr_params);
	}
	return 0;
}
