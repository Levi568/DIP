all: TestFour2struct



TestFour2struct: TestFour2struct.o Four2.o
	gcc -g -Wall -o TestFour2struct TestFour2struct.o Four2.o -lm

Four2.o: Four2.c Four2.h Four2_Private.h
	gcc -g -Wall -c Four2.c

  
TestFour2struct.o: TestFour2struct.c Four2.h cplx.h
	gcc -g -Wall -c TestFour2struct.c

clean:
	rm *.o
