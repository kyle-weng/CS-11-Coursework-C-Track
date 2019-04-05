#
# CS 11: Makefile for C track, assignment 5.
#

CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic

all: arrayOperations pointerOperations

arrayOperations: arrayOperations.o memcheck.o
	$(CC) arrayOperations.o memcheck.o -o arrayOperations

pointerOperations: pointerOperations.o memcheck.o
	$(CC) pointerOperations.o memcheck.o -o pointerOperations

memcheck.o: memcheck.c memcheck.h
	$(CC) $(CFLAGS) -c memcheck.c

arrayOperations.o: arrayOperations.c memcheck.h
	$(CC) $(CFLAGS) -c arrayOperations.c

pointerOperations.o: pointerOperations.c memcheck.h
	$(CC) $(CFLAGS) -c pointerOperations.c

test: testArrayOperations testPointerOperations

testArrayOperations:
	./arrayOperations 75 100

testPointerOperations:
	./pointerOperations 75 100

checkArrayOperations:
	c_style_check arrayOperations.c

checkPointerOperations:
	c_style_check pointerOperations.c

cleanArrayOperations:
	rm -f arrayOperations *.o

cleanPointerOperations:
	rm -f pointerOperations *.o

clean: cleanArrayOperations cleanPointerOperations
