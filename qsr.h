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
   int PEAKS[30];
   int PEAKScount[30];      //INCLUDES ALL PEAK COUNTS
   int PEAKS[200];
   int PEAKScount[200];
   int Xp[3];
   unsigned long counter;
   int R_peak[1];
   int RecentRR[30];        //INCLUDES TIME INTERVAL BETWEEN ALL R-PEAKS (ALSO THOSE FOUND USING SEARCHBACK)
   int RecentRR_OK[30];     //INCLUDES TIME INTERVAL BETWEEN R-PEAKS NOT FOUND USING SEACHBACK
   int RR_average1;
   int RR_average2;
   int RR_low;
   int RR_high;
   int RR_miss;
   int RR_count[30];        //INCLUDES ALL R-PEAK COUNTS
   int RR;                  //MOST RECENT INTERVAL BETWEEN TWO R-PEAKS
   int RR_count[30];
   int RR;
   int WARNING;
} QSR_params;

// QSR FUNCTION PROTOTYPES
void peakDetection(QSR_params *params);
void updateParams1(QSR_params *params);
void updateParams2(QSR_params *params);
void updateParams3(QSR_params *params);
void calculateRR(QSR_params *params);
char findPeak(QSR_params *params);
char searchBack(QSR_params *params);


QSR_params initQSRParams(QSR_params *params);

#endif // QSR_H
