CC=gcc
ARGS=-Wall -Wextra

Library: book.o bookArray.o CuTest.o bookArrayTest.o
	$(CC) ${ARGS} -o $@ $^

%.o:
	$(CC) ${ARGS} -c $*.c
