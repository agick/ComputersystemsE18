#include "qsr.h"
#include "filters.h"
#include <stdio.h>

void displayData(QSR_params *params)
{
	printf("%s\t", "TIME");
	printf("%s\t", "RPEAK");
	printf("%s\t", "PULS");
	printf("\n");
	printf("%lu\t", params->counter/250);
	printf("%d\t", params->R_peak[0]);
	if(params->RR_average1 != 0) {
		printf("%d\t", 15000/params->RR_average1);
	} else {
		printf("%s\t", "UNDEF");
	}
	if(params->R_peak[0] < 2000){ printf("%s\t", "WARNING: LOW RPEAK VALUE"); }
	if(params->WARNING >= 5){ printf("%s\t", "WARNING: 5+ MISSED RPEAKS"); }
	printf("\n\n");
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
	printf("%d\t", params->THRESHOLD2);
	printf("\n");
}



