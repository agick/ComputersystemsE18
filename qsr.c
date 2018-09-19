#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>

void peakDetection(QSR_params *params)
{

}


void updateParams1(QSR_params *params) {
    params->NPKF = 0.125 * params->PEAKS[0] + 0.875 * params->NPKF;
    params->THRESHOLD1 = params->NPKF + 0.25 * (params->SPKF - params->NPKF);
    params->THRESHOLD2 = 0.5 * params->THRESHOLD1;

    // Gør plads til ny peak i peak-arrayet
    params->PEAKS = rightShiftArray(params->PEAKS);
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

    params->R_peak[0] = params->PEAKS[0];
    params->SPKF = 0.125 * params->PEAKS[0] + 0.875 * params->SPKF;

    // Beregner gennemsnit af RR-intervaller
    int sum1 = 0;
    for (int i = 0; i <= 7; i++) {
        sum1 += params->RR_interval1[i];
    }
    params->RR_average1 = sum1/8;

    // Beregner gennemsnit af RR-intervaller fra peaks mellem RR_LOW og RR_HIGH der ikke er fundet via. searchback
    int sum2 = 0;
    for (int i = 0; i <= 7; i++) {
        sum2 += params->RR_interval2[i];
    }
    params->RR_average2 = sum2/8;

    params->RR_low = 0.92 * params->RR_average2;
    params->RR_high = 1.19 * params->RR_average2;
    params->MISS = 1.66 * params->RR_average2;
    params->THRESHOLD1 = params->NPKF + 0.25 * (params->SPKF - params->NPKF);
    params->THRESHOLD2 = 0.5 * params->THRESHOLD1;

    // Gør plads til ny peak i peak-arrayet
    params->PEAK = rightShiftArray(params->PEAKS);

}



char findPeak(QSR_params *params){


	if ((params->Xp[0] < params->Xp[1]) && (params->Xp[1] > params->Xp[2])) {

		//Skubber alle peaks én gang mod højre.
		params->PEAKS =rightShiftArray(params->PEAKS);

		//Gemmer nu den nyest fundne værdi i PEAKS
		params->PEAKS[0]=params->Xp[1];

		return 1;
}
	else {
		return 0;}

}

void searchBack(QSR_params *params) {


	// PROBLEM! Den skal ikke køre de samme igen!
	//så i for-loopet skal der være en counter der kører videre fra
	// sidste vi kiggede på???

		int i;

		//Herunder skal vi kigge alle PEAK igennem
		//Hvis den møder en PEAK >T2, så
		//... skal den rightshifte R_PEAK
		//.... og gemme PEAK[i] på R_PEAK[0]
		for(i = (sizeof(params->PEAKS) / sizeof(int))-1; i > 0; i--){
			if (params->PEAKS[i]>params->THRESHOLD2){
				params->R_peak =rightShiftArray(params->R_peak);
				params->R_peak[0] = params->PEAKS[i];
				break;}
		}
		params->SPKF=0.25*params->R_PEAKS[0]+0.75*params->SPKF;

		params->RR_interval1[0]=params->counter;

		//Beregner gennemsnit af RR
		int sum=0;
		for(int i=0;i<=7;i++){
			sum+=params->RR_interval1[i];
		}
		params->RR_average1=sum/8;
		params->RR_low=0.92*params->RR_average1;
		params->RR_high=1.16*params->RR_average1;
		params->RR_miss=1.66*params->RR_average1;
		params->THRESHOLD1=params->NPKF+0.25*(params->SPKF - params->NPKF)
		params->THRESHOLD2=0.5*params->THRESHOLD1


		//skal tjekke om det er noise eller lign.
		//nu skal den køre vores algoritme forfra
		//sætter SB=1
		params->SB=1;
		//Kør vores algoritme forfra?






}

