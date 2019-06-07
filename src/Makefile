all: Library

%.o:
    gcc -c $@

Library: book.o bookArray.o CuTest.o bookArrayTest.o
    gcc -o $@ $^
