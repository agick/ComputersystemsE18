#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>

void peakDetection(QRS_params *params)
{

}


char findPeak (QRS_params *params){

	if (params->XP[0] < params->XP[1]) && (params->XP[1] > params->XP[2]){

		//Skubber alle peaks én gang mod højre.
		params->PEAKS =rightShiftArray(params->PEAKS)

		//Gemmer nu den nyest fundne værdi i PEAKS
		PEAKS[0]=XP[1];

		return 1;
}
	else {
		return 0;}

}

void searchBack(QRS_params *params) {


	// PROBLEM! Den skal ikke køre de samme igen!
	//så i for-loopet skal der være en counter der kører videre fra
	// sidste vi kiggede på???

		int i;

		//Herunder skal vi kigge alle PEAK igennem
		//Hvis den møder en PEAK >T2, så
		//... skal den rightshifte R_PEAK
		//.... og gemme PEAK[i] på R_PEAK[0]
		for(i = (sizeof(params->PEAK) / sizeof(int))-1; i > 0; i--){
			if params->PEAKS[i]>Threshold2
				params->R_PEAKS =rightShiftArray(params->R_PEAKS);
				R_peaks[0] = Peaks[i];
				break;
		}
		params->SPKF=0.25*R_PEAKS[0]+0.75*params->SPKF;
		params->RR_interval1[0]=params->Counter;

		//Beregner gennemsnit af RR
		int sum=0;
		for(int i=0;i<=7;i++){
			sum+=params->RR_interval1[i];
		}
		params->RR_average1=sum/8
		params->RR_low=0.92*params->RR_average1;
		params->RR_high=1.16*params->RR_average1;
		params->RR_miss=1.66*params->RR_average1;
		params->THRESHOLD1=params->NPKF+0.25*(params->SPKF - params->NPKF)


	// Nu skal vi teste om denne faktisk bare er noise eller?
	//Sætter SB=1, da det er en searchback.
	 params->SB=1;
	 // Calculater RR
	 int SB_RR=calculateRR(QRS_params *params)

	 if (RR_low <SB_RR<RR_high)
		 updateParams2(SB_RR)
		 //Vi har nu behandlet SB
		 params->SB=0;
		else
			if SB_RR>RR_miss

			searchBack()

	 //Vi har nu behandlet SB
	 params->SB=0;


	 // hvis ja, updateParams3()!


}



