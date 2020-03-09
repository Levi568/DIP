#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include "wr.h"
#include "sobel.h"

int main(int argc, char *argv[]){
	int min = INT_MAX;     //set minimum doubled value
	int max = 0;	        //set maximum doubled value

	unsigned sizeX; 	        //image width
	unsigned sizeY; 	        //image height
    unsigned levels;            //image brightness
	unsigned char *image;       //image 1D array
    unsigned char *outputMRI;   //mri image output
    int *data;                  //data type can be either int or float
    int *data_sobel;
  
	//read image from file
	readImage("mri.pgm", &sizeX, &sizeY, &levels, &image);
	
	data = (int*)calloc(sizeof(int),(sizeX+2)*(sizeY+2));       //allocate 258x258
        data_sobel =(int*)calloc(sizeof(int),(sizeX+2)*(sizeY+2));
	outputMRI = (unsigned char *)malloc(sizeX*sizeY);
    
/************************* Image Processing *******************************/
    
    //put original image pixel values in data array, prepare for the padding
    if(data){
        for(int i=1; i<sizeX+1; i++){
            for(int j=1; j<sizeY+1; j++){
                data[i*(sizeX+2) + j] = image[(i-1)*sizeX + (j-1)];
            }
        }
    }
    
    //Apply Sobel filter
    sobel(data, data_sobel);
    
    //Normalization
    for(int i = 0; i < (sizeX+2)*(sizeY+2); i++){
        if (data_sobel[i] < min)
            min = data_sobel[i];
        if (data_sobel[i] > max)
            max = data_sobel[i];
    }
    for(int i = 0; i < (sizeX+2)*(sizeY+2); i++){
        data_sobel[i] = levels*(data_sobel[i]-min)/(max-min);
    }
    
    //put sobel image back to 256x256 size
    for(int i=1; i<sizeX+1; i++){
        for(int j=1; j<sizeY+1; j++){
            outputMRI[(i-1)*sizeX + (j-1)] = data_sobel[i*(sizeX+2) + j];
        }
    }
    
    //write sobel image to file
    writeImage("EdgeImage.pgm", sizeX, sizeY, levels, outputMRI);
    
    //Set a threshold T and make sobel image to be binary
    int T = 30;
    for(int i = 0; i < (sizeX+2)*(sizeY+2); i++){
        if(data_sobel[i] > T)
            data_sobel[i] = levels;
        else
            data_sobel[i] = 0;
    }
	
    //put sobel image back to 256x256 size
    for(int i=1; i<sizeX+1; i++){
        for(int j=1; j<sizeY+1; j++){
             outputMRI[(i-1)*sizeX + (j-1)] = data_sobel[i*(sizeX+2) + j];
        }
    }
    
    //write image to file
    writeImage("BinaryEdgeImage.pgm", sizeX, sizeY, levels, outputMRI);

    free(data);
}
