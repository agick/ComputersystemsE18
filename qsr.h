#ifndef QSR_H
#define QSR_H

// Header file for QRS functionality 
// it is recommended to use the structure "QRS_parameters"
// to organize all variables and parameters

typedef struct QSR_params
{ // Structure for QRS parameters
   int SPKF;
   int NPKF; 
   int THRESHOLD1;
   int THRESHOLD2;
   int PEAKS[200];
   int PEAKScount[200];
   int Xp[3];
   unsigned long counter;
   int R_peak[1];
   int RecentRR[30]; // Indeholder intervaller fra alle R-peaks
   int RecentRR_OK[30]; // Inderholder intervaller fra alle R-peaks der ikke er fundet via. seachback
   int RR_average1;
   int RR_average2;
   int RR_low;
   int RR_high;
   int RR_miss;
   int RR_count[30];
   int RR;
   int WARNING;
} QSR_params;

// Feel free to change and add methods
void peakDetection(QSR_params *params);
void updateParams1(QSR_params *params);
void updateParams2(QSR_params *params);
void updateParams3(QSR_params *params);
void calculateRR(QSR_params *params);
char findPeak(QSR_params *params);
char searchBack(QSR_params *params);


QSR_params initQSRParams(QSR_params *params);

#endif // QSR_H
