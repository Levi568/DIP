all: TestFFTcpp TestFFT.o Image_FFT.o

TestFFTcpp: TestFFT.o Image_FFT.o
	c++ -g -Wall -o TestFFTcpp TestFFT.o Image_FFT.o -lm

TestFFT.o: TestFFT.cpp Image_FFT.h
	g++ -g -Wall -c TestFFT.cpp
	
Image_FFT.o: Image_FFT.cpp Image_FFT.h
	g++ -g -Wall -c Image_FFT.cpp


clean:
	rm *.o
