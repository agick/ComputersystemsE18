#include "qsr.h"
#include "filters.h"
#include <stdio.h>

void displayData(QSR_params *params)
{
	printf("%s\t", "TIME");
	printf("%s\t", "RPEAK");
	printf("%s\t", "PULS");
	printf("\n");
	printf("%lu\t", params->counter);
	printf("%d\t", params->R_peak[0]);
	printf("%d\t", params->RR_average1);
	if(params->R_peak[0] < 2000){ printf("%s\t", "WARNING"); }
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




