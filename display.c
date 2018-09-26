#include "qsr.h"
#include "filters.h"

void display(QSR_params *params)
{
	printf("%d\t", params->counter);
	printf("%d\t", params->Xp[0]);
	printf("%d\t", params->PEAKS[0]);
	printf("%d\t", params->R_peak[0]);
	printf("\n");
	fflush(stdout);
}


printf("%d\t", filters_params.X[0]);
printf("%d\t", filters_params.lpfX[0]);
printf("%d\t", filters_params.hpfX[0]);
printf("%d\t", filters_params.derX);
printf("%d\t", filters_params.sqrX[0]);
