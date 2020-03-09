#include <stdio.h>
#include <stdlib.h>
#include "wr.h"

int main(int argc, char *argv[]){
	unsigned sizeX; 	//image width
	unsigned sizeY; 	//image height
	unsigned char *image;   //image 1D array
	unsigned levels;        //image brightness

	readImage("mri.pgm", &sizeX, &sizeY, &levels, &image);
	int max = 256; 	
	for(int i=0; i<256; i++){
		for(int j=128; j<256; j++)
			image[i*max + j] = 0;		
	}
	writeImage("mri2.pgm", sizeX, sizeY, levels, image);


	free(image);
	return 0;
}
