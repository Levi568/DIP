//Peter Mack
//writen in 2016 as a student
//modified in 2019 as a TA
#ifndef IMAGE_FFT_H
#define IMAGE_FFT_H

#include <complex>
#include <vector>
using namespace std;
//static class for taking fft of an image
//static class needed for function pointers
class Image_FFT
{
public:
  static void FFT(vector<complex<float> > *im, 
                   unsigned sX, 
                   unsigned sY, 
                   bool inv = false);

private:
  static complex<float>& X(int i);
  static complex<float>& Y(int i);
  
  static void Shift();
  
  static vector<complex<float> > *image;
  static unsigned sizeX;
  static unsigned sizeY;
  
  static unsigned rr;
  
  static void Four1(complex<float>& (*DATA)(int),
                    int nn, 
                    int isign);
};

#endif
