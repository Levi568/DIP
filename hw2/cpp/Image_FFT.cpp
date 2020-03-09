#include "Image_FFT.h"
#include <cstdio>
using namespace std;
//Pointer to working Image
vector<complex<float> > *Image_FFT::image;
//working image size
unsigned Image_FFT::sizeX;
unsigned Image_FFT::sizeY;
//working counter
unsigned Image_FFT::rr;

//index working image elments by x axis
complex<float>& Image_FFT::X(int i){
  return image->at(i + rr*sizeX);
}

//index working image elments by y axis
complex<float>& Image_FFT::Y(int i){
  return image->at(rr + i*sizeX);
}

//center spectrum in frequency domain by inverting some pixels in
//the spatial domain
void Image_FFT::Shift(){
  for(unsigned j = 0; j < sizeY; j++){
    for(unsigned i = 0; i < sizeX; i++){
      image->at(i+j*sizeX) *= ((i+j) % 2) ? -1 : 1;
    }
  }
}

//compute 2d FFT of image:  WARNING: Not thread safe
void Image_FFT::FFT(vector<complex<float> > *im, //image
                    unsigned sX, //width
                    unsigned sY, //height
                    bool inv){   //inverse fft when true
  //transfer image and size to static variables
  image = im;
  sizeX = sX;
  sizeY = sY;

  int isign = inv ? 1 : -1;
  //invert every other pixel in spacial domain for centering in frequency domain
  //for forward fft
  if(!inv){
    Shift();
  }

  //run 1D fft for each row
  for(rr = 0; rr < sizeY; rr++){
    Four1(Image_FFT::X,sizeX,isign);
  }

  //run 2D fft for each column
  for(rr = 0; rr < sizeX; rr++){
    Four1(Image_FFT::Y, sizeY, isign);
  }

  //correct magnitude and uncenter result for inverse FFT
  if(inv){
    for(unsigned i = 0; i < sizeX*sizeY; i++){
      image->at(i) /= sizeX*sizeY;
    }
    Shift();
  }
}

//macro for fft
#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp

//1D Fast Four Transform Provided by Professor Megherbi
void Image_FFT::Four1(std::complex<float>& (*DATA)(int),int nn,int isign)
{
        int mmax, m, i, jstep, j;
        double wtemp, theta;
        complex<float> w, wp;
        complex<float> temp;
        i = 0;
        for (j=0; j<nn; j += 1) {
                if (i > j) {
                        SWAP(DATA(i),DATA(j));
                }
                m = nn/2;
                while (m >= 1 && i >= m) {
                        i -= m;
                        m >>= 1;
                }
                i += m;
        }
        mmax = 1;
        while (nn > mmax) {
                jstep = mmax*2;
                theta = 2*asin(1)/(isign*(mmax));
                wtemp = sin(0.5*theta);
                wp = complex<float>(-2.0 * wtemp * wtemp, sin(theta));
                w = complex<float>(1.0,0.0);
                for (m=0; m<mmax; m+=1) {
                        for (j=m; j<nn; j+=jstep) {
                                i = j + mmax;
                                temp = w * DATA(i);
                                DATA(i) = DATA(j)-temp;
                                DATA(j) += temp;
                        }
                        w = w * wp + w;
                }
                mmax = jstep;
        }
}
