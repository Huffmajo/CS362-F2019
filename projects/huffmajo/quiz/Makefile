# makefile for testme.c
#
# 'make all' to compile
# 'testme' to run program
# 'gcov testme.c' to see coverage
# 'gcov testme.c -b' to see branch coverage
# 'make clean' removes the executable

CC=gcc
TARGET=testme

all:	
	gcc testme.c -coverage -fpic -lm -o $(TARGET)

clean:
	rm $(TARGET)
