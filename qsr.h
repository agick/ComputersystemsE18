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
   int RR_interval1[1]; // Indeholder intervaller fra alle R-peaks
   int RR_interval2[1]; // Inderholder intervaller fra alle R-peaks der ikke er fundet via. seachback
   int RR_average1;
   int RR_average2;
   int RR_low;
   int RR_high;
   int RR_miss;
   int SB;              // En "boolean" der skal tjekke om det peak der bliver behandlet er fundet via. searchback
   
} QSR_params;

// Feel free to change and add methods
void peakDetection(QSR_params *params);

#endif // QSR_H
