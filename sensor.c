#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>

int getNextData(FILE *file) {

	if (file == NULL) {
	        printf("The input data file is empty.\n");
	        return 0;
	}
	int i;
	fscanf(file, "%d", &i);
		 return i;

   // return sensor value
}

FILE* openfile(const char* filename) {
   FILE *file = fopen(filename,"r");

   return file;
}
