#include "sensor.h"
#include "filters.h"
#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>

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

	printf("%s\t", "Num");
	printf("%s\t", "Input");
	printf("%s\t", "LPF");
	printf("%s\t", "HPF");
	printf("%s\t", "DRV");
	printf("%s\t", "SQR");
	printf("%s\t", "MWI");
	printf("%s\n", "PEAKS");

	int i = 0;
	int j = 500;
	int k;
	//RUN PROGRAM
	while(j > 0) {
		j--;

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

		// husk at sætte SB=0?

		peakDetection(&qsr_params);


		//PRINT VALUES
		printf("%d\t", 500-j);
		printf("%d\t", filters_params.X[0]);
		printf("%d\t", filters_params.lpfX[0]);
		printf("%d\t", filters_params.hpfX[0]);
		printf("%d\t", filters_params.derX);
		printf("%d\t", filters_params.sqrX[0]);
		printf("%d\t", qsr_params.Xp[0]);
		printf("%d\n", qsr_params.PEAKS[0]);

	}
         // Read Data from Sensor





    //lowPassFilter();            // Filter Data



    //peakDetection(&qsr_params); // Perform Peak Detection


    puts("hello world");
	return 0;
}


/* ============================================================================
 * Tjek samhørighed med hvornår der rightShiftes - gennen hele forløbet i figuren
 *
 *
 *
 */

