# makefile for testme.c
#
# 'make all' to compile
# 'testme' to run program
# 'gcov testme.c -b' to see coverage/branch coverage

CC=gcc
TARGET=testme

all:	
	gcc testme.c -coverage -fpic -lm -o $(TARGET)

clean:
	rm $(TARGET)
