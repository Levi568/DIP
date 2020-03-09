#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
unsigned sizeX; 	//image width
unsigned sizeY; 	//image height
unsigned char *image;   //image 1D array
unsigned levels;

//read image from file
FILE *iFile = fopen("mri.pgm","r"); // iFile point to the image
if(iFile == 0) return 1;
if(3!=fscanf(iFile, "P5 %d %d %d ", &sizeX, &sizeY, &levels)) return 1;  //%d decimal , level means brightness
image = (unsigned char *) malloc(sizeX*sizeY);
fread(image, sizeof(unsigned char), sizeX*sizeY, iFile);
fclose(iFile);

int max = 256; 	
for(int i=0; i<256; i++){
	for(int j=i+128; j<i+256; j++)
		image[i*max + j] = 0;		
}

//write image to file
iFile = fopen("mri2.pgm","w");
if(iFile == 0) return 1; //error handling
fprintf(iFile, "P5 %d %d %d ",sizeX,sizeY, 255);//write header
fwrite(image, sizeof(unsigned char), sizeX*sizeY, iFile);//write binary image
fclose(iFile);


return 0;
}
