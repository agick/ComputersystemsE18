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
   int PEAKS[9];
   int Xp[3];
   int counter;
   int R_peak[1];
   int RR_interval1[1];
   int RR_interval2[1];
   int RR_average1;
   int RR_average2;
   int RR_low;
   int RR_high;
   int RR_miss;
   int SB;
   
} QSR_params;

// Feel free to change and add methods
void peakDetection(QSR_params *params);
int findPeak (QSR_params *params);
void searchBack(QSR_params *params);

#endif // QSR_H
