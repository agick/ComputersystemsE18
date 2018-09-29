#ifndef SENSOR_H
#define SENSOR_H
#include <stdio.h>
#include <stdlib.h>



// Header file for the sensor functionality


FILE* openfile(const char* filename);
int getNextData(FILE *file);



#endif // SENSOR_H