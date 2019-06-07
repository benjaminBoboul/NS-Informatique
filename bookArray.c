#include <assert.h>
#include "bookArray.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct BookArray {
    IBook books[10];
    IBookArray *next;
};

IBookArray bookaNew() {
    IBookArray this = calloc(1, sizeof(struct BookArray));
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
    while (this->books[i]) {
        i++;
        if
    }
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
    return -1;
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
    while (this->books[i]) {i++;}
    return i;
}

void grow(IBookArray this) {
}