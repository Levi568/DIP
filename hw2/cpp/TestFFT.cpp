#include <cstdio>
#include <cstdio>
#include <cmath>
#include <vector>
#include <complex>
#include "Image_FFT.h"
using namespace std;

int main(int argc, char *argv[]){
  /* 3 arrays with the following meaning */
  /* data -->FFT --> spectrum --> IFFT --> output */
  vector<complex<float> > data, spectrum, output;
  unsigned n = 256; //size of 2D data (nxn)


  /* since fourl destroys the input array with the output */
  /* use the output of the FFT as the input value */
  spectrum = data;

  //call 2D fft
  Image_FFT::FFT(&spectrum,n,n,false);

  /*copy spectrum into output and call inverse FFT */
  output = spectrum;
  Image_FFT::FFT(&output,n,n,true);

}

