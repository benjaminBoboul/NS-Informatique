#include <assert.h>
#include "bookArray.h"
#include <stdlib.h>
#include <string.h>

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
    this->books[0] = book;
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
    int i = 0;
    while (this->books[i] != book) {i++;}
	return i;
}

void bookaInsertAt(IBookArray this, int i, IBook book) {
    this->books[i] = book;
}

void bookaRemoveAt(IBookArray this, int i) {
    // [book1, book2, book3]
    this->books[i] = null;
}

void bookaRemoveLast(IBookArray this) {
    if(bookaSize(this) != -1) this->books[bookaSize(this)] = null;
}

void bookaSet(IBookArray this, int i, IBook book) {
    this->books[i] = book;
}

int bookaSize(IBookArray this) {
    int i = 0;
    while(this[i] != '\0') {i++;}
	return i;
}

void grow(IBookArray this) {
    this->next = bookaNew()
}