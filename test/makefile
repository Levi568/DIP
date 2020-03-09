all: rwTest

rwTest: rwTest.o wr.o
	gcc -g -Wall -o rwTest rwTest.o wr.o -lm

wr.o: wr.c wr.h 
	gcc -g -Wall -c wr.c

rwTest.o: rwTest.c wr.h
	gcc -g -Wall -c rwTest.c

clean:
	rm *.o
