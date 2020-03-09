#include "wr.h"
#include <stdio.h>
#include <stdlib.h>
void readImage(char *filename, unsigned *sizeX, unsigned *sizeY, unsigned *levels, unsigned char **image){
	FILE *iFile = fopen(filename,"r"); // iFile point to the image
	if(iFile == NULL || 3!=fscanf(iFile, "P5 %d %d %d ", sizeX, sizeY, levels)) printf("error");  
	*image = (unsigned char *) malloc(*sizeX * *sizeY);
	fread(*image, sizeof(unsigned char), *sizeX * *sizeY, iFile);
	fclose(iFile);
}

void writeImage(char *filename, unsigned sizeX, unsigned sizeY, unsigned levels, unsigned char image[]){
	FILE *iFile = fopen(filename,"w");
	if(iFile == 0) printf("error"); //error handling
	fprintf(iFile, "P5 %d %d %d ",sizeX,sizeY, 255);//write header
	fwrite(image, sizeof(unsigned char), sizeX*sizeY, iFile);//write binary image
	fclose(iFile);
}
