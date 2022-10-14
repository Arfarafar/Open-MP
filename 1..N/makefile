CC = gcc
CFLAGS = -fopenmp

all: a.out


a.out: 1.o
	$(CC) -fopenmp -o $@ $^


1.o: N1.c
	$(CC) -c $(CFLAGS) -o $@ $<


clean:
	rm -rf a.out *.o


.PHONY: clean

run:
    ./a.out 
