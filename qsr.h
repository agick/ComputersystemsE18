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
   int PEAKS[8];
   int PEAKScount[8];      //INCLUDES ALL PEAK COUNTS
   int Xp[3];              //WINDOW OF THREE PEAKS
   unsigned long counter;  //TIME UNIT
   int R_peak[2];
   int RecentRR[8];        //INCLUDES TIME INTERVAL BETWEEN ALL R-PEAKS (ALSO THOSE FOUND USING SEARCHBACK)
   int RecentRR_OK[8];     //INCLUDES TIME INTERVAL BETWEEN R-PEAKS NOT FOUND USING SEACHBACK
   int RR_average1;
   int RR_average2;
   int RR_low;
   int RR_high;
   int RR_miss;
   int RR_count[30];       //INCLUDES ALL R-PEAK COUNTS
   int RR;                 //MOST RECENT INTERVAL BETWEEN TWO R-PEAKS
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
