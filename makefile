#
#
#

all: test

test: test.o
	 test.o -o test

test.o: test.cpp
	 test.cpp -o test.o 

clean:
	rm -rf *.o test
