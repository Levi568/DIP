#include <stdio.h>
#include <stdlib.h>
#include "sobel.h"

void sobel(int *data, int *data_sobel){
    unsigned w = 258;
    unsigned maskWidth = 3;
    int *data_h;
    int *data_v;
    signed char h[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    signed char v[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    
    data_h = (int*)calloc(sizeof(int),w*w);
    data_v = (int*)calloc(sizeof(int),w*w);
    
    for (int i = 0; i < w; i++){                     // rows
        for (int j = 0; j < w; j++){                 // columns
            for (int m = 0; m < maskWidth; m++){       // sub rows
                for (int n = 0; n < maskWidth; n++){   // sub columns
                    int ii = i + m;
                    int jj = j + n;
                    
                    if(ii < w && jj < w){
                        data_h[i*w + j] += data[ii*w + jj] * h[m*maskWidth + n]; //horizontal
                        data_v[i*w + j] += data[ii*w + jj] * v[m*maskWidth + n]; //vertical
                    }
                }
            }
        }
    }
    for(int i = 0; i < w*w; i++){
        data_sobel[i] = abs(data_h[i]) + abs(data_v[i]);
    }
}
