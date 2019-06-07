all: Library

%.o:
	gcc -c $*.c

Library: book.o bookArray.o CuTest.o bookArrayTest.o
	gcc -o $@ $^
