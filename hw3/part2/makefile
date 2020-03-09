all: hw3-2

hw3-2: hw3-2.o wr.o sobel.o smooth.o
	gcc -g -Wall -o hw3-2 hw3-2.o smooth.o sobel.o wr.o -lm

wr.o: wr.c wr.h
	gcc -g -Wall -c wr.c

hw3-2.o: hw3-2.c wr.h sobel.h smooth.h
	gcc -g -Wall -c hw3-2.c

sobel.o: sobel.c sobel.h
	gcc -g -Wall -c sobel.c

smooth.o: smooth.c smooth.h
	gcc -g -Wall -c smooth.c

clean:
	rm *.o
