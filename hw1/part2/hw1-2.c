#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	unsigned sizeX; 	//image width
	unsigned sizeY; 	//image height
	unsigned char *image;   //image 1D array
	unsigned char *store;   //store resized image
	unsigned levels;	//image brightness

	//read image from file
	FILE *iFile = fopen("mri.pgm","r"); // iFile point to the image
	if(iFile == 0) return 1;
	if(3!=fscanf(iFile, "P5 %d %d %d ", &sizeX, &sizeY, &levels)) return 1;
	image = (unsigned char *) malloc(sizeX * sizeY);
	fread(image, sizeof(unsigned char), sizeX*sizeY, iFile);
	fclose(iFile);

	store = (unsigned char *) malloc(sizeX/2 * sizeY/2);

	int max = 256;
	for(int i=0; i<128; i++){
		for(int j=0; j<128; j++){
			store[i*(max/2) + j] = image[i*max*2 + j*2]; //store resized image to store[]
		}
	}

	free(image);  //free image memory

	//write image to file
	iFile = fopen("mri2-2.pgm","w");
	if(iFile == 0) return 1; //error handling
	fprintf(iFile, "P5 %d %d %d ", sizeX/2,sizeY/2, 255); //write header
	fwrite(store, sizeof(unsigned char), sizeX/2*sizeY/2, iFile); //write binary image
	fclose(iFile);
	return 0;
}
