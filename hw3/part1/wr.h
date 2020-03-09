#ifndef WR_H
#define WR_H

//read, write function
void readImage(char *filename, unsigned *sizeX, unsigned *sizeY, unsigned *levels, unsigned char **image);
void writeImage(char *filename, unsigned sizeX, unsigned sizeY, unsigned levels, unsigned char image[]);
	
#endif
