#include <stdio.h>
#include <stdlib.h>
#include "smooth.h"

void smooth(int *data, int *data_smooth){
    unsigned w = 258;
    unsigned maskWidth = 3;
    int *data_s;
    signed char s[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    
    data_s = (int*)calloc(sizeof(int),w*w);
    
    
    for (int i = 0; i < w; i++){                     // rows
        for (int j = 0; j < w; j++){                 // columns
            for (int m = 0; m < maskWidth; m++){       // sub rows
                for (int n = 0; n < maskWidth; n++){   // sub columns
                    int ii = i + m;
                    int jj = j + n;
                    
                    if(ii < w && jj < w){
                        data_s[i*w + j] += data[ii*w + jj] * s[m*maskWidth + n]; //smooth
                
                    }
                }
            }
        }
    }
    for(int i = 0; i < w*w; i++){
        data_smooth[i] = data_s[i];
    }
}
