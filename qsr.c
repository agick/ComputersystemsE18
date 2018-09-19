#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>

void peakDetection(QSR_params *params)
{

}

void updateParams1(QSR_params *params) {
    params->NPKF = 0.125 * params->PEAK[0] + 0.875 * params->NPKF;
    params->THRESHOLD1 = params->NPKF + 0.25 * (params->SPKF - params->NPKF);
    params->THRESHOLD2 = 0.5 * params->THRESHOLD1;

    // Gør plads til ny peak i peak-arrayet
    params->PEAK = rightShiftArray(params->PEAK);
}

void calculateRR(QSR_params *params) {
    params->RR_interval1[0] = params->counter;
    params->RR_interval1 = rightShiftArray(params->RR_interval1);
}

void updateParams2(QSR_params *params) {

    // Tilføjer ikke-searchback peak-interval til RR_interval2
    if (!(params->SB)){
    params->RR_interval2[0] = params->counter;
    }

    params->R_peaks[0] = PEAK[0];
    params->SPKF = 0.125 * params->PEAK[0] + 0.875 * params->SPKF;

    // Beregner gennemsnit af RR-intervaller
    int sum1 = 0;
    for (int i = 0; i <= 7; i++) {
        sum1 += params->RR_interval1[i];
    }
    params->Average1 = sum/8;

    // Beregner gennemsnit af RR-intervaller fra peaks mellem RR_LOW og RR_HIGH der ikke er fundet via. searchback
    int sum2 = 0;
    for (int i = 0; i <= 7; i++) {
        sum2 += params->RR_interval2[i];
    }
    params->Average2;

    params->RR_LOW = 0.92 * params->Average2;
    params->RR_HIGH = 1.19 * params->Average2;
    params->MISS = 1.66 * params->Average2;
    params->THRESHOLD1 = params->NPKF + 0.25 * (params->SPKF - params->NPKF);
    params->THRESHOLD2 = 0.5 * params->THRESHOLD1;

    // Gør plads til ny peak i peak-arrayet
    params->PEAK = rightShiftArray(params->PEAK);

}

