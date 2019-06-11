#include <assert.h>
#include "bookArray.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BOOK_ARRAY_DEFAULT_SIZE 10

struct BookArray {
    size_t allocatedMemorySize;
    IBook *books;
};

IBookArray bookaNew() {
    IBookArray this = calloc(1, sizeof(struct BookArray));
    this->allocatedMemorySize = BOOK_ARRAY_DEFAULT_SIZE * sizeof(IBook);
    this->books = calloc(1, this->allocatedMemorySize);
    return this;
}

/*
 * bookaDelete
 */
void bookaDelete(IBookArray this) {
    free(this);
}

/*
 * bookaAppend
 */
void bookaAppend(IBookArray this, IBook book) {
    int i = 0;
    while(this->books[i] != NULL) {
        i++;
        if (i > this->allocatedMemorySize)
            grow(this);
    }
    printf("Inserting book at index %d.\n", i);
    this->books[i] = book;
}

/*
 * bookaGet
 */
IBook bookaGet(IBookArray this, int i) {
    return this->books[i];
}

/*
 * bookaIndexOf
 */
int bookaIndexOf(IBookArray this, IBook book) {
    int i = -1;
    for(int j = 0; j != bookaSize(this) ; j++) {if (this->books[i] == book) i = j;}
    return i;
}

void bookaInsertAt(IBookArray this, int i, IBook book) {
}

void bookaRemoveAt(IBookArray this, int i) {
}

void bookaRemoveLast(IBookArray this) {
}

void bookaSet(IBookArray this, int i, IBook book) {
}

int bookaSize(IBookArray this) {
    int i = 0;
    while (this->books[i] != NULL) {i++;}
    return i;
}

void grow(IBookArray this) {
    void *new_books;
    printf("<#%p> size : %d\n", &this->books, this->allocatedMemorySize);
    this->allocatedMemorySize += BOOK_ARRAY_DEFAULT_SIZE * sizeof(IBook);
    new_books = realloc(this->books, this->allocatedMemorySize);
    if (new_books != NULL) this->books = new_books;
    printf("<#%p> new size : %d\n", &this->books, this->allocatedMemorySize);
}