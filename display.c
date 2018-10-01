#include "qsr.h"
#include "filters.h"
#include <stdio.h>

void displayNames()
{
	printf("%s\t", "TIME");
	printf("%s\t", "RPEAK");
	printf("%s\t", "PULSE");
	printf("\n");
}

void displayData(QSR_params *params)
{
	if(params->R_peak != params->RPEAK_old){
		printf("%lu\t", params->RR_count[0]/250);
		printf("%d\t", params->R_peak);
		if(params->RR_average1 != 0) {
				printf("%d\t", 15000/params->RR_average1);
			} else {
				printf("%s\t", "UNDEF");
			}
	}

	if(params->PEAKS[0] != params->PEAK_old){
		if(params->PEAKS[0] < 2000 && params->PEAKS[0] != 0 && params->PEAKS[0] > params->THRESHOLD1){

			printf("%s\t", "WARNING: LOW RPEAK VALUE!");
			printf("%s", "(TIME: ");
			printf("%d\t", params->PEAKScount[0]);
			printf("%s", "PEAKVALUE: ");
			printf("%d", params->PEAKS[0]);
			printf("%s\t", ")");
			printf("\n");
		}
		if(params->WARNING > 5){
			printf("%s\t", "WARNING: 5+ MISSED INTERVALS");
			printf("%s\t", "(TIME: ");
			printf("%d", params->PEAKScount[0]);
			printf("%s\t", ")");
			printf("\n");
		}

	}

	if(params->R_peak != params->RPEAK_old){
		printf("\n");
	}
	params->RPEAK_old = params->R_peak;
	params->PEAK_old = params->PEAKS[0];
}

void displayFilters(FILTERS_params *params)
{
	printf("%d\t", params->X[0]);
	printf("%d\t", params->lpfX[0]);
	printf("%d\t", params->hpfX[0]);
	printf("%d\t", params->derX);
	printf("%d\t", params->sqrX[0]);
	printf("%d\t", params->Y);
	printf("\n");
}

void displayQSR(QSR_params *params)
{
	printf("%d\t", params->THRESHOLD1);
	//printf("%d\t", params->THRESHOLD2);
	printf("\n");
}



