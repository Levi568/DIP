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
	unsigned char *outputMRI;  //mri image output

	unsigned sizeX; 	   //image width
	unsigned sizeY; 	   //image height
	unsigned char *image;      //image 1D array
	unsigned levels;           //image brightness

	unsigned order = 2;        //LPF order
	float D;		   //distance to the image center 
	float H;                   
	unsigned D0 = 10;          //cut off value

	//read image from file
	readImage("mri.pgm", &sizeX, &sizeY, &levels, &image);

	cplx *data;
	
	data = (cplx*)calloc(sizeof(cplx),n*n);
	spectrum_m = (double *)malloc(sizeof(double)*n*n);
	output_n = (unsigned char *)malloc(n*n);
	outputMRI = (unsigned char *)malloc(n*n);

	//put image pixel values to data real part
	if(data){
		for(int i=0; i<256; i++){
			for(int j=0; j<256; j++)
				data[i*256 + j].real = image[i*256 + j];		
		}
	} 
	
	//do Fourier transform
	fft_Four2((float*) data,n,n,false);  
	
	//apply BWLPF to both data real part and imaginary part 
	for(int i=0; i<256; i++)
		for(int j=0; j<256; j++){
		 	D = sqrt(pow((i - 128),2) + pow((j - 128),2));
		 	H = 1/(1 + pow((D/D0),2*order));
			data[i*256+j].real *= H;
		        data[i*256+j].imag *= H;	
		}
	

	//calculate the magnitude of spectrum
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

 	//write output mri image to file
	writeImage("mri2.pgm", sizeX, sizeY, levels, output_n);
	
	//do Inverse Fourier transform
	fft_Four2((float*) data,n,n,true); 

	for(i=0;i<n*n;i++)
		outputMRI[i] = data[i].real;

	//write mri image to file
	writeImage("mri3.pgm", sizeX, sizeY, levels, outputMRI);

	free(data);
	free(spectrum_m);
	free(output_n);  
}

