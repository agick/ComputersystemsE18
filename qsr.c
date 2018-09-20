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
        sum1 += (params->RR_interval1[i]-params->RR_interval1[i+1]);
    }
    params->RR_average1 = sum1/8;

    // Beregner gennemsnit af RR-intervaller fra peaks mellem RR_low og RR_high der ikke er fundet via. searchback
    int sum2 = 0;
    for (int i = 0; i <= 7; i++) {
        sum2 += (params->RR_interval2[i]-params->RR_interval2[i+1]);
    }
    params->RR_average2 = sum2/8;

    params->RR_low = 0.92 * params->RR_average2;
    params->RR_high = 1.19 * params->RR_average2;
    params->RR_miss = 1.66 * params->RR_average2;
    params->THRESHOLD1 = params->NPKF + 0.25 * (params->SPKF - params->NPKF);
    params->THRESHOLD2 = 0.5 * params->THRESHOLD1;

    // Gør plads til ny peak i peak-arrayet
    params->PEAKS = rightShiftArray(params->PEAKS);

}



char findPeak(QSR_params *params){

	if ((params->Xp[0] < params->Xp[1]) && (params->Xp[1] > params->Xp[2])) {

		//Skubber alle peaks én gang mod højre.
		int i;
			for(i = (sizeof(params->PEAKS) / sizeof(int))-1; i > 0; i--){
				params->PEAKS[i] = params->PEAKS[i-1];
			}

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


        /* Er det ikke oplagt her at lave et while her? Fx:
        int i = 0;
        while (!(params->PEAKS[i] > THRESHOLD2)) {
            i++;
        } */

		for(i = (sizeof(params->PEAKS) / sizeof(int))-1; i > 0; i--){

			if (params->PEAKS[i]>params->THRESHOLD2) {

                //skubber til højre
                int u;
                for(u = (sizeof(params->R_peak) / sizeof(int))-1; u > 0; u--){
                		params->R_peak[u] = params->R_peak[u-1];
                	}
                //gemmer i R_peak
                params->R_peak[0] = params->PEAKS[i];

                //Opdaterer en masse parametre
                params->SPKF=0.25*params->PEAKS[i]+0.75*params->SPKF;
                params->RR_interval1[0]=params->counter;
                //Beregner gennemsnit af RR
                int sum=0;
                for(int i=0;i<=7;i++){
                	sum+=(params->RR_interval1[i]-params->RR_interval1[i+1]);
                	}
                params->RR_average1=sum/8;
                params->RR_low=0.92*params->RR_average1;
                params->RR_high=1.16*params->RR_average1;
                params->RR_miss=1.66*params->RR_average1;
                params->THRESHOLD1=params->NPKF+0.25*(params->SPKF - params->NPKF);
                params->THRESHOLD2=0.5*params->THRESHOLD1;

                /* Skubber PEAKS til venstre indtil peaket efter searchback-peaket ligger på PEAKS[0]

                 while (!(params->PEAKS[0] == params->PEAKS[i])) {
                    int w;
                    for(w = 0; w < (sizeof(params->PEAKS) / sizeof(int)); w++){
                        params->PEAKS[0] = params->PEAKS[1];
                    }
                }
                 */

                break; //Denne bør breake for-loopet.
            }
		}





		//skal tjekke om det er noise eller lign.
		//nu skal den køre vores algoritme forfra
		//sætter SB=1. Som betyder at der kører en runde med searchback.
		params->SB=1;
		//Kør vores algoritme forfra?
		// Her skal der kaldes calculate igen osv... step2()?
		params->SB=0;




}

