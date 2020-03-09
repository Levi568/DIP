#include <stdio.h>
#include <stdlib.h>
#include "Four2.h"
#include "cplx.h"
#include <math.h>
#include <float.h>
#include <limits.h>

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

int main(int argc, char *argv[]){
	double min = DBL_MAX;      //set minimum doubled value 
	double max = 0.;	   //set maximum doubled value 	
	double *spectrum_m;        //spectrum magnitude
	
	unsigned i;
	unsigned n = 256; 	   //size of 2D data in both directions 
	unsigned char *output_n;   //normalized spectrum output
	unsigned char *outputCake; //cake image output

	unsigned sizeX; 	   //image width
	unsigned sizeY; 	   //image height
	unsigned char *image;      //image 1D array
	unsigned levels;           //image brightness

	//read image from file
	readImage("cake.pgm", &sizeX, &sizeY, &levels, &image);

	cplx *data;

	data = (cplx*)calloc(sizeof(cplx),n*n);
	spectrum_m = (double *)malloc(sizeof(double)*n*n);
	output_n = (unsigned char *)malloc(n*n);
	outputCake = (unsigned char *)malloc(n*n);

	//put the image pixels values to data real part
	if(data){
		for(int i=0; i<256; i++){
			for(int j=0; j<256; j++)
				data[i*256 + j].real = image[i*256 + j];		
		} 
	}
	
	//Fourier Transform
	fft_Four2((float*) data,n,n,false);  

	//calculate the magnitude of spectrum and put it to spectrum_m
	for(i = 0; i < n*n; i++){
           	spectrum_m[i] = sqrt(pow(data[i].real,2) + pow(data[i].imag,2));
	}
	
	//select the min and max in spectrum_m and do the normalization 
	for(i = 0; i < n*n; i++){
		if (spectrum_m[i] < min)
		   	min = spectrum_m[i];
		if (spectrum_m[i] > max)
			max = spectrum_m[i];	
	}
	for(i = 0; i < n*n; i++){
	   	output_n[i] = 255*(spectrum_m[i]-min)/(max-min);
	}
	
	//write normalized spectrum magnitude image to file
	writeImage("cake2.pgm", sizeX, sizeY, levels, output_n);

	//Inverse Fourier transform
	fft_Four2((float*) data,n,n,true); 

	for(i = 0; i < n*n; i++){
	   	outputCake[i] = data[i].real; 
	}
	
	//write output cake image to file
	writeImage("cake3.pgm", sizeX, sizeY, levels, outputCake);

	free(data);
	free(spectrum_m);
	free(output_n);  
}

