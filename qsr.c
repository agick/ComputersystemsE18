#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>

void peakDetection(QSR_params *params)
{
	params->counter++;
	if(findPeak(params)){														//FIND PEAK
		int i;																	//IF PEAK IS FOUND RIGHT SHIFT PEAKS ARRAY
		for(i = (sizeof(params->PEAKS) / sizeof(int))-1; i > 0; i--){			//RIGHT SHIFT
			params->PEAKS[i] = params->PEAKS[i-1];								//RIGHT SHIFT
		}																		//RIGHT SHIFT
		params->PEAKS[0]=params->Xp[1];											//SET PEAKS[0] TO FOUND PEAK
		for(i = (sizeof(params->PEAKScount) / sizeof(int))-1; i > 0; i--){		//RIGHT SHIFT PEAKS COUNT ARRAY
			params->PEAKScount[i] = params->PEAKS[i-1];							//RIGHT SHIFT
		}																		//RIGHT SHIFT
		params->PEAKScount[0]=params->counter;									//SET PEAKSCOUNT[0] TO FOUND PEAK
		if(params->PEAKS[0] > params->THRESHOLD1){								//CHECK IF PEAK IS LARGER THAN THRESHOLD1
			calculateRR(params);												//IF IT IS CALCULATE RR
			if(params->RR_low < params->RR && params->RR < params->RR_high){	//CHECK IF CALCULATED RR IS SMALLER THAN RR_LOW AND HIGHER THAN RR_HIGH
				params->WARNING = 0;
				updateParams2(params);											//IF IT IS UPDATE PARAMS 2
			} else {															//IF NOT
				params->WARNING++;
				if(params->RR > params->RR_miss){								//CHECK IF CALCULATED RR IS HIGHER THAN RR_MISS
					if(searchBack(params)){										//IF IT IS DO A SEARCHBACK
						updateParams3(params);									//IF R_PEAK FOUND UPDATE PARAMS 3
					}															//...
				}																//...
			}																	//...
		} else {																//...
			updateParams1(params);												//IF PEAK WAS NOT LARGER THAN THRESHOLD1 UPDATE PARAMS1
		}																		//...
	}																			//...
}


void updateParams1(QSR_params *params) {
    params->NPKF = 0.125 * params->PEAKS[0] + 0.875 * params->NPKF;				//UPDATE NPKF
    params->THRESHOLD1 = params->NPKF + 0.25 * (params->SPKF - params->NPKF);	//UPDATE THRESHOLD1
    params->THRESHOLD2 = 0.5 * params->THRESHOLD1;								//UPDATE THRESHOLD2
}

void updateParams2(QSR_params *params) {
	int i;																		//INITIALIZE i
	for(i = (sizeof(params->R_peak) / sizeof(int))-1; i > 0; i--){				//RIGHT SHIFT R_PEAK ARRAY
	   	params->R_peak[i] = params->R_peak[i-1];								//RIGHT SHIFT
	}																			//RIGHT SHIFT
	params->R_peak[0] = params->PEAKS[0];										//STORE PEAK AS R_PEAK

	for(i = (sizeof(params->RecentRR) / sizeof(int))-1; i > 0; i--){			//RIGHT SHIFT RECENTRR ARRAY
		params->RecentRR[i] = params->RecentRR[i-1];							//RIGHT SHIFT
	}																			//RIGHT SHIFT
	params->RecentRR[0] = params->RR;											//INPUT RR INTO RECENTRR ARRAY

	for(i = (sizeof(params->RecentRR_OK) / sizeof(int))-1; i > 0; i--){			//RIGHT SHIFT INTERVAL2 ARRAY
	   	params->RecentRR_OK[i] = params->RecentRR_OK[i-1];						//RIGHT SHIFT
	}																			//RIGHT SHIFT
    params->RecentRR_OK[0] = params->RR;										//SET RR_INTERVAL2[0] TO COUNTER2 VALUE

    params->SPKF = 0.125 * params->PEAKS[0] + 0.875 * params->SPKF;				//UPDATE SPKF

    int sum1 = 0;																//INITIALIZE SUM1
    int samples = 0;															//INITIALIZE SAMPLES
    for (int i = 0; i <= 7; i++) {												//CALCULATE SUM OF LAST 8 RECENTRR
        sum1 += params->RecentRR[i];											//...
        if(params->RecentRR[i] != 0){ samples++; }								//IF VALUE IS NOT 0, SAMPLES++
    }																			//...
    if(samples != 0){ params->RR_average1 = sum1/samples; }						//SET RR_AVERAGE1 TO SUM1 DIVEDED BY SAMPLES

    int sum2 = 0;																//INITIALIZE SUM2
    samples = 0;
    for (int i = 0; i <= 7; i++) {												//CALCULATE SUM OF LAST 8 INTERVAL2
        sum2 += params->RecentRR_OK[i];											//...
        if(params->RecentRR_OK[i] != 0){ samples++; }
    }																			//...
    if(samples != 0){ params->RR_average2 = sum2/samples; }						//SET RR_AVERAGE2 TO AVERAGE OF SUM2

    params->RR_low = 0.92 * params->RR_average2;								//UPDATE RR_LOW
    params->RR_high = 1.19 * params->RR_average2;								//UPDATE RR_HIGH
    params->RR_miss = 1.66 * params->RR_average2;								//UPDATE RR_MISS
    params->THRESHOLD1 = params->NPKF + 0.25 * (params->SPKF - params->NPKF);	//UPDATE THRESHOLD1
    params->THRESHOLD2 = 0.5 * params->THRESHOLD1;								//UPDATE THRESHOLD2

}

void updateParams3(QSR_params *params) {
	params->SPKF=0.25*params->PEAKS[0]+0.75*params->SPKF;						//UPDATE SPKF
	int sum1 = 0;
	int samples = 0;															//INITIALIZE SUM1
	for (int i = 0; i <= 7; i++) {												//CALCULATE SUM OF LAST 8 INTERVAL1
		sum1 += params->RecentRR[i];											//...
		if(params->RecentRR[i] != 0){ samples++; }
	}																			//...
	if(samples != 0){ params->RR_average1 = sum1/samples; }						//SET RR_AVERAGE1 TO AVERAGE OF SUM1

	params->RR_low=0.92*params->RR_average1;									//UPDATE RR_LOW
	params->RR_high=1.16*params->RR_average1;									//UPDATE RR_HIGH
	params->RR_miss=1.66*params->RR_average1;									//UPDATE RR_MISS
	params->THRESHOLD1=params->NPKF+0.25*(params->SPKF - params->NPKF);			//UPDATE THRESHOLD1
	params->THRESHOLD2=0.5*params->THRESHOLD1;									//UPDATE THRESHOLD2
}

void calculateRR(QSR_params *params) {
    int i;
    for(i = (sizeof(params->RR_count) / sizeof(int))-1; i > 0; i--){			//RIGHT SHIFT INTERVAL1 ARRAY
      	params->RR_count[i] = params->RR_count[i-1];
    }
    params->RR_count[0] = params->PEAKScount[0];
    params->RR = params->RR_count[0]-params->RR_count[1];
}

char findPeak(QSR_params *params){
	if (params->Xp[0] < params->Xp[1] && params->Xp[1] > params->Xp[2]) {		//IF XP ARRAY CONTAINS A PEAK
		return 1;																//RETURN TRUE
	} else {																	//...
		return 0;																//RETURN FALSE
	}
}

char searchBack(QSR_params *params){
	int i = 0;
	int j;
	for(i = 0; i < sizeof(params->PEAKS) / sizeof(int); i++){
		if(params->PEAKScount[i] > params->RR_count[1] && params->PEAKScount[i] < params->RR_count[0]){
			if(params->PEAKS[i] > params->THRESHOLD2){
				for(j = (sizeof(params->RecentRR) / sizeof(int))-1; j > 0; j--){//RIGHT SHIFT RECENTRR ARRAY
					params->RecentRR[j] = params->RecentRR[j-1];				//RIGHT SHIFT
				}																//RIGHT SHIFT
				params->RecentRR[0] = params->PEAKScount[i]-params->RR_count[1];//SET RECENTRR TO PEAK FOUND MINUS LAST RR PEAK
				return 1;
			}
		}																		//RETURN TRUE FOR FOUND SEARCHBACK PEAK
	}
	return 0;																	//OTHERWISE RETURN FALSE
}

QSR_params initQSRParams(QSR_params *params)									//INITIALIZE QSR_PARAMS DATA STRUCTURE VARIABLES
{
	int i;
	for(i = 0; i < sizeof(params->PEAKS) / sizeof(int); i++){					//SET ALL PEAK AMPLITUDES TO 0
		params->PEAKS[i] = 0;
	}
	for(i = 0; i < sizeof(params->PEAKScount) / sizeof(int); i++){				//SET ALL PEAK COUNTS TO 0
		params->PEAKScount[i] = 0;
	}
	for(i = 0; i < sizeof(params->Xp) / sizeof(int); i++){						//SET THE THREE PEAK AMPLITUDES IN XP ARRAY TO 0
		params->Xp[i] = 0;
	}
	for(i = 0; i < sizeof(params->RecentRR) / sizeof(int); i++){				//SET ALL RECENTRR INTERVALS TO 0
		params->RecentRR[i] = 150;
	}
	for(i = 0; i < sizeof(params->RecentRR_OK) / sizeof(int); i++){				//SET ALL RECENTRR_OK INTERVALS TO 0
		params->RecentRR_OK[i] = 150;
	}
	for(i = 0; i < sizeof(params->R_peak) / sizeof(int); i++){					//SET ALL R_PEAKS TO 0
		params->R_peak[i] = 0;
	}
	for(i = 0; i < sizeof(params->RR_count) / sizeof(int); i++){				//SET ALL RR_COUNTS TO 0
		params->RR_count[i] = 0;
	}
	params->THRESHOLD1 = 0;														//SET THRESHOLD1 TO 0
	params->THRESHOLD2 = 0;														//SET THRESHOLD2 TO 0
	params->RR_low = 0;															//SET RR_LOW TO 0
	params->RR_high = 0;														//SET RR_HIGH TO 0
	params->RR_miss = 0;														//SET RR_MISS TO 0
	params->counter = 0;														//SET COUNTER TO 0
	params->SPKF = 0;															//SET SPKF TO 0
	params->NPKF = 0;															//SET NPKF TO 0
	params->RR_average1 = 0;													//SET RR_AVERAGE1 TO 0
	params->RR_average2 = 0;													//SET RR_AVERAGE2 TO 0
	params->RR = 0;																//SET RR TO 0
	params->WARNING = 0;														//SET WARNING TO 0
	return *params;																//RETURN INITIALIZED PARAMETERS
}

