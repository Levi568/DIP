all: hw3

hw3: hw3.o wr.o sobel.o
	gcc -g -Wall -o hw3 hw3.o sobel.o wr.o -lm

wr.o: wr.c wr.h
	gcc -g -Wall -c wr.c

hw3.o: hw3.c wr.h sobel.h
	gcc -g -Wall -c hw3.c

sobel.o: sobel.c sobel.h
	gcc -g -Wall -c sobel.c

clean:
	rm *.o
