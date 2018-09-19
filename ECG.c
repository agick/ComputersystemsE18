/* kommentar.11.57
 ============================================================================
 Name        : ECG.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "sensor.h"
#include "array.h"
#include "filters.h"
#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>

// Main function for organizing the program execution.
// The functions and object predefined are just for inspiration.
// Please change orden,names arguments to fit your solution.

int main(void)
{

    //QRS_params qsr_params;       // Instance of the made avaiable through: #include "qsr.h"
    FILTERS_params filters_params;
    filters_params = initFilterParams(&filters_params);

    //OPEN FILE
	FILE *file;                  // Pointer to a file object
	file = openfile("ECG.txt");

	printf("%s\t", "Input");
	printf("%s\t", "LPF");
	printf("%s\t", "HPF");
	printf("%s\t", "DRV");
	printf("%s\t", "SQR");
	printf("%s\n", "MWI");

	int i = 0;
	int j = 100;
	//RUN PROGRAM
	while(j > 0) {
		j--;

		//GET INPUT AND WRITE TO ARRAY X
		i = getNextData(file);
		filters_params.X = rightShiftArray(filters_params.X);
		filters_params.X[0] = i;

		//GO THROUGH ALL FILTERS
		lowPassFilter(&filters_params);
		highPassFilter(&filters_params);
		derivative(&filters_params);
		squaring(&filters_params);
		mwi(&filters_params);

		//WRITE Y VALUE TO XP ARRAY GOING INTO PEAK DETECTION




		//PRINT VALUES
		printf("%d\t", filters_params.X[0]);
		printf("%d\t", filters_params.lpfX[0]);
		printf("%d\t", filters_params.hpfX[0]);
		printf("%d\t", filters_params.derX);
		printf("%d\t", filters_params.sqrX[0]);
		printf("%d\n", filters_params.Y[0]);

	}
         // Read Data from Sensor





    //lowPassFilter();            // Filter Data



    //peakDetection(&qsr_params); // Perform Peak Detection


    puts("hello world");
	return 0;
}


